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
# @file tests/gpio/CMakeLists.txt
# @authors Aaron McBride
# @brief Top level cmake file for the gpio test of the titan project.

cmake_minimum_required(VERSION 3.19)

message(VERBOSE "Titan: Configuring GPIO test target.")

add_executable(titan_test_gpio)

set_target_properties(titan_test_gpio PROPERTIES 
  OUTPUT_NAME "titan_test_gpio.elf"
)

target_link_libraries(titan_test_gpio PRIVATE 
  titan_test_interface
  titan_module_mcu
)

target_include_directories(titan_test_gpio PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/src"
)

# Add all source files for the target below:
target_sources(titan_test_gpio PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/src/main.c"
)