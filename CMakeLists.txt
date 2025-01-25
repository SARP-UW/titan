###################################################################################################
# NOTE -> THIS CMAKE LISTS FILE IS FOR PROJECT DEVELOPMENT ONLY
#         AND SHOULD BE REPLACED AT SOME POINT WITH A PROPER BUILD SYSTEM.
###################################################################################################

# TEMP
set(CMAKE_EXECUTABLE_SUFFIX ".exe")
set(CMAKE_LINK_DIR src/STM32H7x5/link.ld)

# Configure cmake compilers
set(TC_BIN_PATH $ENV{ARM_GNU_TOOLCHAIN}/bin)
set(CMAKE_C_COMPILER ${TC_BIN_PATH}/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER ${TC_BIN_PATH}/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER ${TC_BIN_PATH}/arm-none-eabi-g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY ${TC_BIN_PATH}/arm-none-eabi-objcopy${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJDUMP ${TC_BIN_PATH}/arm-none-eabi-objdump${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_SIZE ${TC_BIN_PATH}/arm-none-eabi-size${CMAKE_EXECUTABLE_SUFFIX})

set(CMAKE_EXE_LINKER_FLAGS_INIT "-nostdlib")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH ${TC_BIN_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Set system info
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Init cmake project
cmake_minimum_required(VERSION 3.15.3)
project(TAL)

# Set language
enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Add executable to be built
set(EXECUTABLE ${PROJECT_NAME}.elf)
add_executable(${EXECUTABLE} 
  test/devboard_startup.S 
  test/main.c
)

# Set include directory
target_include_directories(${EXECUTABLE} PRIVATE
  ${CMAKE_SOURCE_DIR}
)

# Set compiler defines
target_compile_definitions(${EXECUTABLE} PRIVATE
  -D TAL_DEBUG
  -D TAL_ARCH_ARMV7M 
  -D TAL_ARCH_FPU 
  -D TAL_PLATFORM_STMH7X5
  -D TAL_PACKAGE_144
)

# Set compiler config
target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-m7
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -fdata-sections
  -ffreestanding
  -T devboard.ld
  -O2
  -g3
)

# Set linker config
target_link_options(${EXECUTABLE} PRIVATE
  -nostdlib
  -T ${CMAKE_SOURCE_DIR}/${CMAKE_LINK_DIR}
  -mcpu=cortex-m7
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -specs=nano.specs
  -lnosys
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker
  -print-memory-usage
)

# Set pos build commands
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD 
  COMMAND ${CMAKE_SIZE} ${EXECUTABLE}
  COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 ${EXECUTABLE} ${PROJECT_NAME}.s19
  COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
)