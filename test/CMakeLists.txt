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
# @brief CMake lists file for test directory of titan project

# CMake version/includes
cmake_minimum_required(VERSION 3.19)

# Get target port
option(TITAN_TEST_PORT "Default port for test build." "NULL")
if(${TIATN_TEST_PORT} STREQUAL "NULL")
  message(FATAL_ERROR "No port specified for test build.")
endif()

# Initialize test project
project(TITAN_TEST_PROJECT)

# Set language
enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Initialize test executable
add_executable(TITAN_TEST
  "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
)

# Add include directories
target_include_directories(TITAN_TEST 
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Add target titan library
set(TITAN_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")
find_library(TITAN_LIB TITAN_${TITAN_TEST_PORT} ${TITAN_LIB_PATH})
target_link_libraries(TITAN_TEST ${TITAN_LIB})