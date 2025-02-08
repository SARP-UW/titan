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
# @internal
# @file CMakeLists.txt
# @authors Aaron McBride
# @brief CMake lists file for the titan project.

###################################################################################################
# Project Options
###################################################################################################

# Paths to default configuration files
set(DEFAULT_BUILD_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/default_build_config.cmake)
set(DEFAULT_LIB_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config/default_lib_config.cmake)

# Project options
option(TI_TARGET_PORT "Target port to build for." "null")
option(TI_PORT_CONFIG "Path to port configuration file." "null")
option(TI_BUILD_CONFIG "Path to build configuration file." ${DEFAULT_BUILD_CONFIG_PATH})
option(TI_LIB_CONFIG "Path to library configuration file." ${DEFAULT_LIB_CONFIG_PATH})

# Set variable with path to target port directory
set(PORT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/port/${TI_TARGET_PORT})

# Validate set option values
if(NOT EXISTS ${PORT_PATH})
  if(TI_TARGET_PORT STREQUAL "null")
    message(FATAL_ERROR "TI_TARGET_PORT not set.")
  else()
    message(FATAL_ERROR "Invalid target port: ${TI_TARGET_PORT}")
  endif()
endif()
if(NOT EXISTS ${TI_BUILD_CONFIG})
  message(FATAL_ERROR "Invalid path to build configuration file: ${TI_BUILD_CONFIG}")
endif()
if(NOT EXISTS ${TI_LIB_CONFIG})
  message(FATAL_ERROR "Invalid path to library configuration file: ${TI_LIB_CONFIG}")
endif()

###################################################################################################
# Load/Parse Configuration Files
###################################################################################################

# Load/parse build configuration file
message(STATUS "Parsing the build configuration file...")
file(READ ${TI_BUILD_CONFIG} BUILD_CONFIG_JSON)
string(JSON BUILD_CONFIG PARSE ${BUILD_CONFIG_JSON})

# Load/parse library configuration file
message(STATUS "Parsing the library configuration file...")
file(READ ${TI_LIB_CONFIG} LIB_CONFIG_JSON)
string(JSON LIB_CONFIG PARSE ${LIB_CONFIG_JSON})

# Load/parse port configuration file
message(STATUS "Parsing the port configuration file...")
file(READ ${TI_PORT_CONFIG} PORT_CONFIG_JSON)
string(JSON PORT_CONFIG PARSE ${PORT_CONFIG_JSON})

###################################################################################################
# Apply Build Configuration Settings
###################################################################################################

# ARM GCC compiler settings
if(BUILD_CONFIG["compiler_type"] STREQUAL "arm_gcc")

  # Set environment information
  set(CMAKE_SYSTEM_NAME Generic)
  set(CMAKE_SYSTEM_PROCESSOR ARM)

  # Set compiler paths
  set(CMAKE_C_COMPILER ${BUILD_CONFIG["compiler_path"]}/arm-none-eabi-gcc)
  set(CMAKE_CXX_COMPILER ${BUILD_CONFIG["compiler_path"]}/arm-none-eabi-g++)
  set(CMAKE_ASM_COMPILER ${BUILD_CONFIG["compiler_path"]}/arm-none-eabi-gcc)
  set(CMAKE_OBJCOPY ${BUILD_CONFIG["compiler_path"]}/arm-none-eabi-objcopy)
  set(CMAKE_OBJDUMP ${BUILD_CONFIG["compiler_path"]}/arm-none-eabi-objdump)
  set(CMAKE_SIZE ${BUILD_CONFIG["compiler_path"]}/arm-none-eabi-size)

else()
  message(FATAL_ERROR "Invalid compiler type: ${BUILD_CONFIG["compiler"]}")
endif()

# Set language standards
set(CMAKE_C_STANDARD ${BUILD_CONFIG["c_standard"]})
set(CMAKE_CXX_STANDARD ${BUILD_CONFIG["cxx_standard"]})

# Add compiler arguments
foreach(arg IN LISTS BUILD_CONFIG["compiler_args"])
  string(APPEND CMAKE_C_FLAGS " ${arg}")
endforeach()

###################################################################################################
# Setup CMake
###################################################################################################

# Initialize CMake project
cmake_minimum_required(VERSION 3.15.3)
project(TAL)
enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add executable to be built
set(EXECUTABLE ${PROJECT_NAME}.elf)
add_executable(${EXECUTABLE} 
  test/main.c
)

# Set include directory
target_include_directories(${EXECUTABLE} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
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
  -Wl,-start-group
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