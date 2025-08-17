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
# @brief Top level cmake file for the tests directory of the titan project.

cmake_minimum_required(VERSION 3.19)

add_library(titan_test_interface INTERFACE)

target_link_libraries(titan_test_interface INTERFACE
  titan_interface
)

target_compile_options(titan_test_interface INTERFACE
  "-ffunction-sections"
  "-fdata-sections"
  "-Wall" 
  "-Wextra" 
  "-Werror"
  "-g"
  "-Og"
)

target_link_options(titan_test_interface INTERFACE
  "-T${CMAKE_CURRENT_LIST_DIR}/linker.ld"
  "-Wl,--enable-non-contiguous-regions"
  "-Wl,--gc-sections"
)

target_compile_definitions(titan_test_interface INTERFACE
  "TITAN_TEST"
  "DEBUG"
)

# Add all test subdirectories here:
add_subdirectory("gpio")