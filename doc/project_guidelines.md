# Project Guidelines

  ## C++ Rules
  - No dynamic allocation (new, delete)
  - No exceptions (throw, try, catch)
  - No RTTI - run time type information (typeid, dynamic_cast)
  - No standard library

  ## Style
  - Max columns: 100 (prefer ~80).
  - K&R bracket styling.
  - Indent using 2 spaces.
  - Indent wrapped lines using 4 spaces.
  - Always use brackets (even when scope is on the same line).
  - Initialize EVERYTHING using uniform init syntax -> type my_var{...}.
  - No space between function name and argument list -> fn().
  - Single Space between control keyword and condition -> if (), while (), for ()...
  - Only use Cpp style casts.

  ## Key Principle
  - Simplicity.

  ## Good Code Practices
  - Minimize global variables (if needed, minimize scope).
  - Variables should be const, unless there is a good reason not to.
  - Maximize compile time code.
  - Declare everything as late as possible.
  - Minimize scope of all variables.
  - Only use type erasure (void*) if absolutely necessary.
  - Never provide direct access to class fields (encapsulation).
  - Minimize amount of "magic numbers".
  - Prefer small functions.

  ## Good Documentation Practices
  - Thouroughly document all external code (even if it seems exessive).
  - Only provide implementation comments/documentation when it is really necessary.
  - For implementation comments/documentation, explain why, never what:
    - Dont: "This does this and then that" (If this is necessary, the code is poorly written.
      Note however, there are some exceptions to this, especially when interacting with hardware).
    - Do: "This is needed because..." (Only if really necessary though... ideally the code
      should be so clear, that comments like these are only rarely needed).