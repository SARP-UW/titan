/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 Aaron McBride.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * @file common/util/function.h 
 * @authors Aaron McBride 
 * @brief Contains the 'function' class.
 */

#pragma once
#include "common/tmp.h"
#include "common/util/utility.h"
#include "common/util/cstdint.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Function Class Declaration
   **************************************************************************************************/

  template<typename T>
  class function;

  template<typename R, typename... Args>
  class function<R(Args...)> {

    public:

      using ThisType = function<R(Args...)>;

      static constexpr size_t storage_size{8};

      constexpr function();

      constexpr function(nullptr_t);

      template<typename F>
      function(F&& fn);

      constexpr function(R (&fn)(Args...));

      function(const function<R(Args...)>& other);

      function(const function<R(Args...)>&& other);

      constexpr ThisType& operator=(nullptr_t);

      template<typename F>
      constexpr ThisType& operator=(F&& fn);

      constexpr ThisType& operator=(R (&fn)(Args...));

      ThisType& operator=(const function<R(Args...)>& other);

      ThisType& operator=(const function<R(Args...)>&& other);

      constexpr bool swap(function<R(Args...)>&& other);

      [[nodiscard]] constexpr bool has_fn() const;

      [[nodiscard]] constexpr explicit operator bool() const;

      constexpr R operator () (Args... args);

      void target_type() const = delete;

      template<typename T>
      [[nodiscard]] constexpr bool is_target_type() const;

      template<typename T>
      [[nodiscard]] constexpr T* target();

      template<typename T>
      [[nodiscard]] constexpr const T* target() const;

    private:

      using FnPtrT = R (*)(Args...);
      using StorageT = FnPtrT[storage_size / sizeof(FnPtrT)];

      struct TaskSelectorT;

      template<typename T>
      static constexpr TaskSelectorT& callable_task_fn();

      static constexpr TaskSelectorT& static_task_fn();

      alignas(alignof(FnPtrT)) StorageT storage_{};
      TaskSelectorT& (*task_fn_)();

  }; // class function

  template<typename T, typename R, typename... Args>
  [[nodiscard]] constexpr bool operator==(const function<R(Args...)>& func, const T& other);

  template<typename T, typename R, typename... Args>
  [[nodiscard]] constexpr bool operator==(const T& other, const function<R(Args...)>& func);

  template<typename T, typename R, typename... Args>
  [[nodiscard]] constexpr bool operator!=(const function<R(Args...)>& func, const T& other);

  template<typename T, typename R, typename... Args>
  [[nodiscard]] constexpr bool operator!=(const T& other, const function<R(Args...)>& func);


  template<typename R, typename... Args>
  [[nodiscard]] constexpr bool operator==(const function<R(Args...)>& func, nullptr_t);

  template<typename R, typename... Args>
  [[nodiscard]] constexpr bool operator==(nullptr_t, const function<R(Args...)>& func);

  template<typename R, typename... Args>
  [[nodiscard]] constexpr bool operator!=(const function<R(Args...)>& func, nullptr_t);

  template<typename R, typename... Args>
  [[nodiscard]] constexpr bool operator!=(nullptr_t, const function<R(Args...)>& func);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

  } // namespace annoymous

  template<typename R, typename... Args>
  constexpr function<R(Args...)>::function() {};

  template<typename R, typename... Args>
  constexpr function<R(Args...)>::function(nullptr_t) {};

  template<typename R, typename... Args>
  template<typename F>
  function<R(Args...)>::function(F&& fn) {
    static_assert(sizeof(decay_t<F>) < storage_size, 
        "Callable object size cannot exceed storage size.");
    using Dt = decay_t<F>;
    new (&storage_) Dt{forward<F>(fn)};
    task_fn_ = &callable_task_fn<Dt>;
  }

  template<typename R, typename... Args>
  constexpr function<R(Args...)>::function(R (&fn)(Args...)) {
    storage_[0] = &fn;
    task_fn_ = &static_task_fn;
  }

  template<typename R, typename... Args>
  function<R(Args...)>::function(const function<R(Args...)>& other) {
    if (other.has_fn()) {
      other.task_fn_.copy_fn(&other.storage_, &this->storage_);
      this->task_fn_ = other.task_fn_;
    }
  }

  template<typename R, typename... Args>
  function<R(Args...)>::function(const function<R(Args...)>&& other) {
    if (other.has_fn()) {
      other.task_fn_.move_fn(&other.storage_, &this->storage_);
      this->task_fn_ = other.task_fn_;
    }
  }

  template<typename R, typename... Args>
  constexpr function<R(Args...)>& function<R(Args...)>::operator=(nullptr_t) {
    if (has_fn()) {
      task_fn_.dtor_fn(&storage_);
      task_fn_ = nullptr;
    }
    return *this;
  }

  template<typename R, typename... Args>
  template<typename F>
  constexpr function<R(Args...)>& function<R(Args...)>::operator=(F&& fn) {
    if (has_fn()) {
      task_fn_.dtor_fn(&storage_);
    }
    using Dt = decay_t<F>;
    new (&storage_) Dt(forward<F>(fn));
    task_fn_ = &callable_task_fn<Dt>;
    return *this;
  }

  template<typename R, typename... Args>
  constexpr function<R(Args...)>& function<R(Args...)>::operator=(
      R (&fn)(Args...)) {
    if (has_fn()) {
      task_fn_.dtor_fn(&storage_);
    }
    storage_[0] = &fn;
    task_fn_ = &static_task_fn;
    return *this;
  }

  template<typename R, typename... Args>
  function<R(Args...)>& function<R(Args...)>::operator=(
      const function<R(Args...)>& other) {
    if (likely(this != &other)) {
      if (this->has_fn()) {
        this->task_fn_.dtor_fn(&this->storage_);
      }
      if (other.has_fn()) {
        other.task_fn_.copy_fn(&other.storage_, &this->storage_);
      }
      this->task_fn_ = other.task_fn_;
    }
    return *this;
  }

  template<typename R, typename... Args>
  function<R(Args...)>& function<R(Args...)>::operator=(
      const function<R(Args...)>&& other) {
    if (likely(this != &other)) {
      if (this->has_fn()) {
        this->task_fn_.dtor_fn(&this->storage_);
      }
      if (other.has_fn()) {
        other.task_fn_.move_fn(&other.storage_, &this->storage_);
      }
      this->task_fn_ = other.task_fn_;
    }
    return *this;
  }

  template<typename R, typename... Args>
  constexpr bool function<R(Args...)>::swap(function<R(Args...)>&& other) {
    if (likely(this != &other)) {
      if (this->has_fn() && other.has_fn()) {
        StorageT tmp{};
        this->task_fn_.move_fn(&this->storage_, &tmp);
        this->task_fn_.dtor_fn(&this->storage_);
        other.task_fn_.move_fn(&other.storage_, &this->storage_);
        other.task_fn_.dtor_fn(&other.storage_);
        this->task_fn_.move_fn(&tmp, &other.storage_);
        swap(this->task_fn_, other.task_fn_);

      } else if (this->has_fn()) {
        this->task_fn_.move_fn(&this->storage_, &other.storage_);
        this->task_fn_.dtor_fn(&this->storage_);
        other.task_fn_ = exchange(this->task_fn_, nullptr);

      } else if (other.has_fn()) {
        other.task_fn_.move_fn(&other.storage_, &this->storage_);
        other.task_fn_.dtor_fn(&other.storage_);
        this->task_fn_ = exchange(other.task_fn_, nullptr);
      }
      return true;
    }
    return false;
  }

  template<typename R, typename... Args>
  constexpr bool function<R(Args...)>::has_fn() const {
    return task_fn_ != nullptr;
  }

  template<typename R, typename... Args>
  constexpr function<R(Args...)>::operator bool() const {
    return has_fn();
  }

  template<typename R, typename... Args>
  constexpr R function<R(Args...)>::operator () (Args... args) {
    if (unlikely(!has_fn())) {
      sys_error("Null function invoked."); // TODO: Should this be a result?
    }
    return task_fn_.invoke_fn(&storage_, args...);
  }

  template<typename R, typename... Args>
  template<typename T>
  constexpr bool function<R(Args...)>::is_target_type() const {
    if constexpr (is_null_pointer_v<T>) {
      return !has_fn();
    } else if constexpr (is_same_v<decay_t<T>, R (*)(Args...)>) {
      return has_fn() && task_fn_ == &static_task_fn;
    } else {
      return has_fn() && task_fn_ == &callable_task_fn<decay_t<T>>;
    }
  }

  template<typename R, typename... Args>
  template<typename T>
  constexpr T* function<R(Args...)>::target() {
    if (is_target_type<T>()) {
      return reinterpret_cast<T*>(&storage_);
    } else {
      return nullptr;
    }
  }

  template<typename R, typename... Args>
  template<typename T>
  constexpr const T* function<R(Args...)>::target() const {
    if (is_target_type<T>()) {
      return reinterpret_cast<const T*>(&storage_);
    } else {
      return nullptr;
    }
  }

  template<typename R, typename... Args>
  struct function<R(Args...)>::TaskSelectorT {
    void (*copy_fn)(StorageT*, StorageT*);
    void (*move_fn)(StorageT*, StorageT*);
    void (*dtor_fn)(StorageT*);
    R (*invoke_fn)(StorageT*, Args...);
  };

  template<typename R, typename... Args>
  template<typename T>
  constexpr function<R(Args...)>::TaskSelectorT& 
      function<R(Args...)>::callable_task_fn() {
    static TaskSelectorT task_sel{
      [](StorageT* src, StorageT* dst) -> void { // copy_fn
        const T& src_value{*reinterpret_cast<T*>(src)};
        new (dst) T{src_value};
      },
      [](StorageT* src, StorageT* dst) -> void { // move_fn
        T& src_value{*reinterpret_cast<T*>(src)};
        new (dst) T{move(src_value)}; 
      },
      [](StorageT* storage) -> void { // dtor_fn
        T& storage_value{*reinterpret_cast<T*>(storage)};
        storage_value.~T();
      },
      [](StorageT* storage, Args... args) -> R { // invoke_fn
        T& storage_value{*reinterpret_cast<T*>(storage)};
        return storage_value(args...);
      },
    };
    return task_sel;
  }

  template<typename R, typename... Args>
  constexpr function<R(Args...)>::TaskSelectorT& 
      function<R(Args...)>::static_task_fn() {
    static TaskSelectorT task_sel{
      [](StorageT* src, StorageT* dst) -> void { // copy_fn
        (*src)[0] = (*dst)[0]; 
      },
      [](StorageT* src, StorageT* dst) -> void { // move_fn
        (*src)[0] = (*dst)[0]; 
      },
      [](StorageT* storage) -> void { // dtor_fn
        (*storage)[0] = nullptr; 
      },
      [](StorageT* storage, Args... args) -> R { // invoke_fn
        return (*storage_[0])(args...); 
      },
    };
    return task_sel;
  }

} // namespace ti::util