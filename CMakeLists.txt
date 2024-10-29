cmake_minimum_required(VERSION 3.15.3)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE INTERNAL "")

# Get the toolchain cmake file
set(CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/cmake/arm-gcc-toolchain.cmake)

# Declare project
project(titan)

# Set language config
enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set executable and linker file
set(EXECUTABLE ${PROJECT_NAME}.elf)
add_executable(${EXECUTABLE} test/devboard_startup.S 
                             test/main.c)

# Set compiler defines
target_compile_definitions(
  ${EXECUTABLE} PRIVATE -D TI_ARCH_ARMV7 -D TI_ARCH_FPU -D TI_PLATFORM_STMH7)

# Set include directory
target_include_directories(${EXECUTABLE} PRIVATE test)

# Set compiler config
target_compile_options(
  ${EXECUTABLE}
  PRIVATE -mcpu=cortex-m7
          -mthumb
          -mfpu=fpv4-sp-d16
          -mfloat-abi=hard
          -fdata-sections
          -ffreestanding
          -T devboard.ld
          -O2
          -g3)

# Set linker config
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/bin/link/devboard.ld)
target_link_options(
  ${EXECUTABLE}
  PRIVATE
  -T${LINKER_FILE}
  -mcpu=cortex-m7
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -specs=nano.specs
  -lnosys
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker
  -print-memory-usage)

# Print executable size after build
add_custom_command(
  TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_SIZE} ${EXECUTABLE})

# Create hex, bin, and S-Record files after the build
add_custom_command(
  TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len=64 ${EXECUTABLE}
          ${PROJECT_NAME}.s19
  COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)