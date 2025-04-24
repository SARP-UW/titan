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
# @brief CMake lists file for titan project (top-level).

cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_LIST_DIR}/common/cmake/config_parser.cmake")

# Get library configuration file (default or from given path or from presets folder)
set(TI_LIB_CONFIG_PRESET_PATH "${CMAKE_CURRENT_LIST_DIR}/common/lib_config")
set(TI_LIB_DEFAULT_CONFIG "${TI_LIB_CONFIG_PRESET_PATH}/default_config.json")
option(TITAN_LIB_CONFIG "Path or name of library configuration file" "${TI_DEFAULT_LIB_CONFIG}")
if(NOT EXISTS "${TITAN_LIB_CONFIG}")
  string(TOLOWER "${TITAN_LIB_CONFIG}" TI_LIB_CONFIG_PRESET_NAME)
  set(TITAN_LIB_CONFIG "${TI_LIB_CONFIG_PRESET_PATH}/${TI_LIB_CONFIG_PRESET_NAME}_config.json")
  if(NOT EXISTS "${TITAN_LIB_CONFIG}")
    message(FATAL_ERROR "${TITAN_LIB_CONFIG} is not the name/path of a valid configuration file.")
  endif()
endif()

# Get list of C pre-processor definitions from configuration file
ti_parse_config_file("${TITAN_LIB_CONFIG}" TI_LIB_CFG_DEF_LIST)

# Initialize top-level library
add_library(TITAN_TOP INTERFACE)

# Set top-level include directory (public interface)
target_include_directories(TITAN_TOP 
  INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include"
)

# Make compiler define library configuration definitions
target_compile_definitions(TITAN_TOP 
  INTERFACE ${TI_LIB_CFG_DEF_LIST}
)

# Add all ports - they initialize their own libraries and link to top-level.
set(TI_PORT_DIR "${CMAKE_CURRENT_LIST_DIR}/port")
file(GLOB TI_PORT_NAME_LIST RELATIVE "${TI_PORT_DIR}" "${TI_PORT_DIR}/*")
foreach(CUR_PORT_NAME IN LISTS TI_PORT_NAME_LIST)
  add_subdirectory("${TI_PORT_DIR}/${CUR_PORT_NAME}")
endforeach()