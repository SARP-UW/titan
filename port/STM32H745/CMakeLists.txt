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
# @brief CMake lists file for the STM32H745 port.

cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_LIST_DIR}/../common/cmake/config_parser.cmake")

# Get port-specific configuration file
set(TI_STM32H745_CONFIG_PRESET_PATH "${CMAKE_CURRENT_LIST_DIR}/port_config")
set(TI_STM32H745_DEFAULT_CONFIG "${TI_STM32H745_CONFIG_PRESET_PATH}/STM32H745_config.json")
option(TITAN_STM32H745_CONFIG "Path to port configuration file" "${TI_STM32H745_DEFAULT_CONFIG}")
if(NOT EXISTS "${TITAN_STM32H745_CONFIG}")
  string(TOLOWER "${TITAN_STM32H745_CONFIG}" TI_STM32H745_CONFIG_PRESET_NAME)
  set(TITAN_STM32H745_CONFIG "${TI_STM32H745_CONFIG_PRESET_PATH}/${TI_STM32H745_CONFIG_PRESET_NAME}_config.json")
endif()

# Only proceed if configuration file exists and compiler is supported
if(EXISTS "${TITAN_STM32H745_CONFIG}" AND
  ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"))

  # Get list of C pre-processor definitions from configuration file
  ti_parse_config_file("${TITAN_STM32H745_CONFIG}" TI_STM32H745_CFG_DEF_LIST)

  # Initialize STM32H745 port library
  add_library(TITAN_STM32H745 INTERFACE)

  # Link to top level library (contains public include/ti directory)
  target_link_libraries(TITAN_STM32H745 TITAN_TOP)

  # Include port-specific directories in library
  target_include_directories(TITAN_STM32H745 
    INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src"
  )

  # Compiler configuration for GNU-like compilers
  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")

    # Set compilation flags specific to STM32H745
    target_compile_options(TITAN_STM32H745 
      INTERFACE
        "-T ${CMAKE_CURRENT_LIST_DIR}/linker_script/gnu_link.ld"
        "-mcpu=cortex-m4"
        "-mthumb"
        "-mfpu=fpv4-sp-d16"
        "-mfloat-abi=hard"
    )

    # Set linking flags specific to STM32H745
    target_link_options(TITAN_STM32H745 
      INTERFACE
        "-T ${CMAKE_CURRENT_LIST_DIR}/linker_script/gnu_link.ld"
        "-mcpu=cortex-m4"
        "-mthumb"
        "-mfpu=fpv4-sp-d16"
        "-mfloat-abi=hard"
        "-Wl,--gc-sections"
        "-Wl,-start-group"
        "-Wl,--whole-archive"
        "-Xlinker"
        "-print-memory-usage"
    )

    # Make compiler define port configuration definitions
    target_compile_definitions(TITAN_STM32H745 
      INTERFACE 
        ${TI_STM32H745_CFG_DEF_LIST}
        "-D TI_TARGET_STM32H745"
    )

  endif()

endif()