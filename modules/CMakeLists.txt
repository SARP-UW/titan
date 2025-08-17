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
# @file modules/CMakeLists.txt
# @authors Aaron McBride
# @brief Top level cmake file for the modules subdirectory.

cmake_minimum_required(VERSION 3.19)

# Add all active subdirectories
add_subdirectory("common")
add_subdirectory("internal")
add_subdirectory("kernel")
add_subdirectory("mcu")