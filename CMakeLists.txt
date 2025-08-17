# This file is part of the titan project.
# Copyright (c) 2025 UW SARP
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
# 
# @file CMakeLists.txt
# @authors Aaron McBride
# @brief Top level cmake file for the titan project.

cmake_minimum_required(VERSION 3.19)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PREFIX "arm-none-eabi-")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(titan C ASM)

add_library(titan_interface INTERFACE)

target_compile_options(titan_interface INTERFACE
  "-mcpu=cortex-m4" 
  "-mthumb" 
  "-mfpu=fpv4-sp-d16"
  "-ffreestanding"
)

target_link_options(titan_interface INTERFACE
  "-nostartfiles" 
  "-specs=nosys.specs"
)

message(VERBOSE "Titan: Configuring modules.")
add_subdirectory("modules")

option(TITAN_EN_APPS "Enable titan application targets" ON)
if(TITAN_EN_APPS)
  message(VERBOSE "Titan: Configuring application targets.")
  add_subdirectory("apps")
endif()

option(TITAN_EN_TESTS "Enable titan test targets" ON)
if(TITAN_EN_TESTS)
  message(VERBOSE "Titan: Configuring test targets.")
  add_subdirectory("tests")
endif()