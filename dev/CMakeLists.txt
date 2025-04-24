# Aaron McBride
# Cmake file for generating dev builds.

cmake_minimum_required(VERSION 3.19)

# Set cmake toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/resource/arm_gnu_toolchain.cmake")

# Create project
project(TITAN_DEV_PROJECT)

# Configure languages/standards
enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Initialize executable
add_executable(TITAN_DEV
  "${CMAKE_CURRENT_LIST_DIR}/src/main.c"
)

# Select include directory
target_include_directories(TITAN_DEV
  PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src"
)

# Set compilation options
target_compile_options(TITAN_DEV
  "-Wall"
  "-Wextra"
  "-Werror"
  "-O0"
  "-g"
)

# Set titan options
set(TITAN_LIB_CONFIG "${CMAKE_CURRENT_LIST_DIR}/resource/lib_config.json")
set(TITAN_STM32H745_CONFIG "${CMAKE_CURRENT_LIST_DIR}/resource/STM32H745_config.json")

# Include and link titan library
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../CMakeLists.txt" "tmp")
target_link_libraries(TITAN_DEV TITAN_STM32H745)