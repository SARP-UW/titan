# Project Information

  ## General Information
  - This project is currently targetting the STMH745ZI MCU (TFQP 144 package).
    - This MCU uses the ARMv7M arch.
  - This project will be using c11 (possible cpp interface at a later time).
  - This project is currently being compiled with the GNU ARM Embedded toolchain
    compiler (although this main change to regular GCC at some point).
  - This project is using a CMAKE build system.

  ## General Rules
  - K&R bracket style.
  - 100 col. max (prefer ~80).
  - Indent scopes using 2 spaces.
  - Indent wrapped lines using 4 spaces.
  - Name types using snake_case_t.
  - Name functions using snake_case.
  - Name variables using snake_case.
  - All externally visible names should have the prefix "ti_".
  - No space between function names and argument lists -> my_fn(args...)
  - Add a spaces between control statement keywords and condition expressions
    -> if ()... while ()... for ()...

  ## Misc Rules & Info
  - Avoid direct use of any compiler specific features. If a compiler-specific
    feature needs to be used, create an interface for it so that it can be adapted
    to other compilers at a later time.
  - Make sure to include cpp guards at the top and bottom of every file, templates
    for these can be found in the doc/template folder.
  - We can only use the following freestanding C libraries:
    - <float.h>
    - <limits.h>
    - <iso646.h>
    - <stdarg.h>
    - <stddef.h>
    - <stdbool.h>
    - <stdint.h>
    - <stdalign.h>
    - <stdnoreturn.h>

  ## Documentation
  - Documentation for this project uses doxygen so make sure that all non-internal
    documentation is formatted accordingly (see https://www.doxygen.nl/index.html for info).
  - Use only C-style comments for external documentation (style for internal documentation
    does not matter).
  - Try to keep all documentation to a max of 80 col. per line (note inline documentation
    may need to be longer...).
  - Limit internal documentation to only what is really needed.
  - When documenting code/implementation **try to avoid explaining what, and instead**
    **explain why**. *If you need to explain what a piece of code is/does then it*
    *is usually not very good code in the first place since it should be easy to read*
    (note that there are some notable exceptions to this, especially when interacting
    with external hardware!).

  ## Good Practices
  - Minimize number of global variables.
  - Minimize amount of "magic numbers in code".
  - Global variables should almost NEVER be accessible outside of their own
    translation unit (header/source file). If they need to be modified, make
    an interface for that...
  - Never allocate memory, always ask client to do so and pass it to function.
  - Use opaque types when the client will interact with them.
  - Functions should rarely be longer then ~80 lines.
  - All variables should be declared const unless there is a good reason for 
    them not to be.
  - Max of 1 prefix (in addition to ti_) for type/function/variable names.