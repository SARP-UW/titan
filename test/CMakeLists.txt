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
# @brief Cmake file for the titan test target.
# @todo Implement target configuration for ICC-like compilers.

cmake_minimum_required(VERSION 3.19)

# Test target configuration options
option(TITAN_TEST_PORT "Port for titan test target." "STM32H745")
option(TITAN_TEST_LIB_CONFIG "Library configuration for titan test target" "default")
option(TITAN_TEST_PORT_CONFIG "Port configuration for titan test target" "default")

# Verbose output of option values
message(VERBOSE "TITAN: Test target port: ${TITAN_TEST_PORT}")
message(VERBOSE "TITAN: Test library configuration file/preset: ${TITAN_TEST_LIB_CONFIG}")
message(VERBOSE "TITAN: Test port configuration file/preset: ${TITAN_TEST_PORT_CONFIG}")

# Get list of source files for test target
set(TI_TEST_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE TITAN_TEST_SOURCES "${TI_TEST_SRC_DIR}/*.c" "${TI_TEST_SRC_DIR}/*.h")

# Initialize test target and link to titan library
add_executable(TITAN_TEST ${TITAN_TEST_SOURCES})
target_include_directories(TITAN_TEST PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
create_titan_library("TITAN_TEST_LIB" "${TITAN_TEST_PORT}" 
    "${TITAN_TEST_LIB_CONFIG}" "${TITAN_TEST_PORT_CONFIG}")
target_link_libraries(TITAN_TEST PUBLIC "TITAN_TEST_LIB")

# Lists of compiler IDs which share configuration settings (for test target)
set(TI_TEST_GNU_ID_LIST "GNU" "Clang" "ARMClang" "TIClang")
set(TI_TEST_ICC_ID_LIST "ICC" "IAR" "TI" "ARMCC")

# Test target configuration for GNU-like compilers
if("${CMAKE_C_COMPILER_ID}" IN_LIST TI_TEST_GNU_ID_LIST)
  message(DEBUG "TITAN: Using GNU configuration for test target.")
  target_compile_options(TITAN_TEST PUBLIC 
    "-Wall" "-Wextra" "-nostdlib" "-ffreestanding")
  target_link_options(TITAN_TEST PUBLIC 
    "-Wl,-gc-sections" "-Wl,-print-memory-usage")

else() # Error on invalid compiler for test target
  message(NOTICE "TITAN: Target does not support compiler: ${CMAKE_C_COMPILER_ID}.")
  message(NOTICE "TITAN: Supported compilers:")
  foreach(COMPILER_ID ${TI_TEST_GNU_ID_LIST} ${TI_TEST_ICC_ID_LIST})
    message(NOTICE " - ${COMPILER_ID}")
  endforeach()
  message("")
  message(FATAL_ERROR "")
endif()