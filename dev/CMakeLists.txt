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
# @file dev/CMakeLists.txt
# @authors Aaron McBride
# @brief Cmake file for the titan dev target.
# @todo Implement target configuration for ICC-like compilers.

cmake_minimum_required(VERSION 3.19)

# Dev target configuration options
option(TITAN_DEV_PORT "Port for titan dev target." "STM32H745")
option(TITAN_DEV_LIB_CONFIG "Library configuration for titan dev target" "default")
option(TITAN_DEV_PORT_CONFIG "Port configuration for titan dev target" "default")

# Verbose output of option values
message(VERBOSE "TITAN: Dev target port: ${TITAN_DEV_PORT}")
message(VERBOSE "TITAN: Dev library configuration file/preset: ${TITAN_DEV_LIB_CONFIG}")
message(VERBOSE "TITAN: Dev port configuration file/preset: ${TITAN_DEV_PORT_CONFIG}")

# Get list of source files for dev target
set(TI_DEV_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE TITAN_DEV_SOURCES "${TI_DEV_SRC_DIR}/*.c ${TI_DEV_SRC_DIR}/*.h")

# Initialize dev target and link to titan library
add_executable(TITAN_DEV ${TITAN_DEV_SOURCES})
target_include_directories(TITAN_DEV PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
create_titan_library("TITAN_DEV_LIB" "${TITAN_DEV_PORT}" 
    "${TITAN_DEV_LIB_CONFIG}" "${TITAN_DEV_PORT_CONFIG}")
target_link_libraries(TITAN_DEV PUBLIC "TITAN_DEV_LIB")

# Lists of compiler IDs which share configuration settings (for dev target)
set(TI_DEV_GNU_ID_LIST "GNU" "Clang" "ARMClang" "TIClang")
set(TI_DEV_ICC_ID_LIST "ICC" "IAR" "TI" "ARMCC")

# Dev target configuration for GNU-like compilers
if("${CMAKE_C_COMPILER_ID}" IN_LIST TI_DEV_GNU_ID_LIST)
  message(DEBUG "TITAN (DEV): Using GNU compiler configuration for dev target.")
  target_compile_options(TITAN_DEV PUBLIC 
    "-Wall" "-Wextra" "-flto" "-nostdlib" "-ffreestanding")
  target_link_options(TITAN_DEV PUBLIC 
    "-Wl,-gc-sections" "-Wl,-print-memory-usage")

else() # Error on invalid compiler for dev target
  message(NOTICE "TITAN: Target does not support compiler: ${CMAKE_C_COMPILER_ID}.")
  message(NOTICE "TITAN: Supported compilers:")
  foreach(COMPILER_ID ${TI_DEV_GNU_ID_LIST} ${TI_DEV_ICC_ID_LIST})
    message(NOTICE " - ${COMPILER_ID}")
  endforeach()
  message("")
  message(FATAL_ERROR "")
endif()