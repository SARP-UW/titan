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
# @file apps/domecracker/CMakeLists.txt
# @authors Aaron McBride
# @brief Top level cmake file for the domecracker application.

cmake_minimum_required(VERSION 3.19)

message(VERBOSE "Titan: Configuring domecracker application target.")

add_library(titan_app_domecracker_interface INTERFACE)

set_target_properties(titan_app_domecracker_interface PROPERTIES
  OUTPUT_NAME "titan_domecracker.elf"
)

target_link_libraries(titan_app_domecracker_interface INTERFACE
  titan_interface
  titan_module_kernel
  titan_module_mcu
  titan_module_util
)

target_include_directories(titan_app_domecracker_interface INTERFACE
  "${CMAKE_CURRENT_LIST_DIR}/src"
)

# Add all source files for the target below:
target_sources(titan_app_domecracker_interface INTERFACE
  "${CMAKE_CURRENT_LIST_DIR}/src/main.c"
)

target_compile_options(titan_app_domecracker_interface INTERFACE
  "-ffunction-sections"
  "-fdata-sections"
  "-Wall"
  "-Wextra"
  "-Werror"
)

target_link_options(titan_app_domecracker_interface INTERFACE
  "-T${CMAKE_CURRENT_LIST_DIR}/linker.ld"
  "-Wl,--enable-non-contiguous-regions"
  "-Wl,--gc-sections"
)

add_executable(titan_app_domecracker_dev)

target_link_libraries(titan_app_domecracker_dev PRIVATE
  titan_app_domecracker_interface
)

target_compile_options(titan_app_domecracker_dev PRIVATE
  "-g"
  "-Og"
)

target_compile_definitions(titan_app_domecracker_dev PRIVATE
  "DEBUG"
)

add_executable(titan_app_domecracker_rel)

target_link_libraries(titan_app_domecracker_rel PRIVATE
  titan_app_domecracker_interface
)

target_compile_options(titan_app_domecracker_rel PRIVATE
  "-O2"
)