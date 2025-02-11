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

# CMake version/includes
cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/util/json_parser.cmake")

# Get port configuration file
set(TITAN_STM32H745_DEFAULT_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/port_config/default_config.json")
option(TITAN_STM32H745_CONFIG "Path to port configuration file" ${TITAN_STM32H745_DEFAULT_CONFIG})
if(NOT EXISTS ${TITAN_STM32H745_CONFIG})
  set(TITAN_STM32H745_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/port_config/${TITAN_STM32H745_CONFIG}_config.json")
  if(NOT EXISTS ${TITAN_STM32H745_CONFIG})
    message(FATAL_ERROR "${TITAN_STM32H745_CONFIG} is not a name/path to a valid configuration file for the STM32H745 port.")
  endif()
endif()

# Parse port configuration file
parse_port_config(TITAN_STM32H745_CFG_DEF_LIST ${TITAN_STM32H745_CONFIG})

# Initialize port library
add_library(TITAN_STM32H745 INTERFACE)

# Link to top level titan library
target_link_libraries(TITAN_STM32H745 TITAN_TOP)

# Set library include directories
target_include_directories(TITAN_STM32H745 
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Find library sources
FILE(GLOB_RECURSE TITAN_STM32H745_INT_H "${CMAKE_CURRENT_SOURCE_DIR}/src" "*.h")
FILE(GLOB_RECURSE TITAN_STM32H745_INT_C "${CMAKE_CURRENT_SOURCE_DIR}/src" "*.c")

# Set library sources
target_sources(TITAN_STM32H745
  INTERFACE
    ${TITAN_STM32H745_INT_H}
    ${TITAN_STM32H745_INT_C}
)

# Configure GNU compiler
if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")

  # Set library compilation options
  target_compile_options(TITAN_STM32H745 
    INTERFACE
      -T "${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts/gnu_link.ld"
      -mcpu=cortex-m4
      -mthumb
      -mfpu=fpv4-sp-d16
      -mfloat-abi=hard
  )

  # Set library linking options
  target_link_options(TITAN_STM32H745 
    INTERFACE
      -T "${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts/gnu_link.ld"
      -mcpu=cortex-m4,
      -mthumb,
      -mfpu=fpv4-sp-d16,
      -mfloat-abi=hard
  )

  # Set compiler definitions (from lib/port config)
  target_compile_definitions(TITAN_STM32H745 
    INTERFACE ${TITAN_STM32H745_CFG_DEF_LIST};
    TI_TARGET_${TITAN_PORT}
  )

# Invalid compiler
elseif()
  message(FATAL_ERROR "Compiler not supported.")
endif()