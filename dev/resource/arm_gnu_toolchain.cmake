# Aaron McBride
# Toolchain file for ARM GNU toolchain

# Set toolchain path/prefix
set(TOOLCHAIN_PATH $ENV{ARM_GNU_TOOLCHAIN})
set(TOOLCHAIN_PREFIX "arm-none-eabi-")

# Set the system information variables
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Set the compiler flags (required to pass tests)
set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs")

# Set the compiler IDs
set(CMAKE_C_COMPILER_ID "GNU")
set(CMAKE_CXX_COMPILER_ID "GNU")

# Set the compiler paths
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++.exe")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}objcopy.exe")
set(CMAKE_SIZE_UTIL "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}size.exe")

# Set cmake configuration
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Set C compiler flags
set(CMAKE_C_FLAGS_DEBUG_INIT "-g3 -Og -Wall -pedantic -DDEBUG")
set(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG_INIT} CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE_INIT "-O3 -Wall")
set(CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE_INIT} CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_MINSIZEREL_INIT "-Os -Wall")
set(CMAKE_C_FLAGS_MINSIZEREL ${CMAKE_C_FLAGS_MINSIZEREL_INIT} CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g -Wall")
set(CMAKE_C_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO_INIT} CACHE STRING "" FORCE)

# Set C++ compiler flags
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g3 -Og -Wall -pedantic -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG_INIT} CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE_INIT} CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-Os -Wall")
set(CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_CXX_FLAGS_MINSIZEREL_INIT} CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g -Wall")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT} CACHE STRING "" FORCE)
