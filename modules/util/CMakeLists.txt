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
# @file modules/util/CMakeLists.txt
# @authors Aaron McBride
# @brief Top level cmake file for the util module.

cmake_minimum_required(VERSION 3.19)

message(VERBOSE "Titan: Configuring util module.")

add_library(titan_module_util STATIC)

target_link_libraries(titan_module_util PRIVATE
  titan_interface
)

target_include_directories(titan_module_util
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
  PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src"
)

# Add all source files for the target below:
target_sources(titan_module_util PRIVATE
  #NONE
)