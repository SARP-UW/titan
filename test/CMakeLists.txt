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
# @file test/CMakeLists.txt
# @authors Aaron McBride
# @brief CMake lists file for test directory of titan project.

cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_LIST_DIR}/../CMakeLists.txt")

# Create project for test build
project(TITAN_TEST)

# Iterate through all ports
set(TI_PORT_DIR "${CMAKE_CURRENT_LIST_DIR}/../port")
file(GLOB TI_PORT_NAME_LIST RELATIVE "${TI_PORT_DIR}" "${TI_PORT_DIR}/*")
foreach(CUR_PORT_NAME IN LISTS TI_PORT_NAME_LIST)

  # Create target for each port, with test/src/main.c as source file
  add_executable(TITAN_${CUR_PORT_NAME}_TEST
    "${CMAKE_CURRENT_LIST_DIR}/src/main.c"
  )

  # Configure target languages/standards
  enable_language(C ASM)
  set(CMAKE_C_STANDARD 99)
  set(CMAKE_C_EXTENSIONS OFF)
  set(CMAKE_C_STANDARD_REQUIRED ON)

  # Include all test in the src directory.
  target_include_directories(TITAN_${CUR_PORT_NAME}_TEST 
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src"
  )

  # Set compiler options
  target_compile_options(TITAN_${CUR_PORT_NAME}_TEST
    "-Wall" 
    "-Wextra" 
    "-Werror" 
    "-O0" 
    "-g"
  )

endforeach()