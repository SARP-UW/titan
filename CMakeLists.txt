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
# @brief CMake lists file for the titan project.

# CMake version/includes
cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/util/config_parser.cmake")

# Get library configuration file
set(TITAN_LIB_DEFAULT_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_config/default_config.json")
option(TITAN_LIB_CONFIG "Path or name of library configuration file" ${TITAN_LIB_DEFAULT_CONFIG})
if(NOT EXISTS ${TITAN_LIB_CONFIG})
  set(TITAN_LIB_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_config/${TITAN_LIB_CONFIG}_config.json")
  if(NOT EXISTS ${TITAN_LIB_CONFIG})
    message(FATAL_ERROR "${TITAN_LIB_CONFIG} is not a name/path to a valid library configuration file.")
  endif()
endif()

# Parse library configuration file
parse_lib_config(TITAN_LIB_CFG_DEF_LIST ${TITAN_LIB_CONFIG})

# Initialize top level titan library
add_library(TITAN_TOP INTERFACE)

# Set library include directories
target_include_directories(TITAN_TOP
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")

  # Set linking options
  target_link_options(TITAN_TOP 
    INTERFACE
      -Wl, --gc-sections
      -Wl, -start-group
      -Wl, --whole-archive
      -Xlinker
      -print-memory-usage 
  )

  # Set compiler defines (library configuration)
  target_compile_definitions(TITAN_TOP 
    INTERFACE ${TITAN_LIB_CFG_DEF_LIST}
  )

# Unsupported compiler
else()
  message(FATAL_ERROR "Unsupported compiler: ${CMAKE_C_COMPILER_ID}")
endif()

# Add port libraries
set(TITAN_PORT_DIR "${TITAN_PORT_PATH}/port")
file(GLOB TITAN_PORT_LIST RELATIVE ${TITAN_PORT_DIR} "${TITAN_PORT_DIR}/*")
foreach(PORT_DIR IN ${TITAN_PORT_LIST})
  add_subdirectory("${TITAN_PORT_DIR}/${PORT_DIR}")
endforeach()
