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
# @brief Top-level cmake file for the titan project.

cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_LIST_DIR}/common/cmake/config_parser.cmake")

# Declare top-level project
project(TITAN)

# Declare path variable for use in functions
set(TI_BASE_PATH "${CMAKE_CURRENT_LIST_DIR}")
set(TI_LIB_CONFIG_PRESET_DIR "${TI_BASE_PATH}/common/lib_config")

# Library build system configuration options
option(TITAN_TEST_TARGET "Enable test target" OFF)
option(TITAN_DEV_TARGET "Enable dev target" OFF)

# Verbose output for configuration options
message(VERBOSE "TITAN: Test target: ${TITAN_TEST_TARGET}")
message(VERBOSE "TITAN: Dev target: ${TITAN_DEV_TARGET}")

# Creates a titan library target with the specified configuration.
# LIB_NAME: (string) Name of the library target to create
# PORT: (string) Name of the target port (hardware platform).
# LIB_CONFIG: (string) Path or name of library configuration file.
# PORT_CONFIG: (string) Path or name of port configuration file.
function(create_titan_library LIB_NAME PORT LIB_CONFIG PORT_CONFIG)

  # Print status message (and configuration details if verbose)
  message(STATUS "TITAN: Configuring library: ${LIB_NAME}...")
  message(VERBOSE "TITAN: Target port: '${PORT}'")
  message(VERBOSE "TITAN: Library configuration file/preset: ${LIB_CONFIG}")
  message(VERBOSE "TITAN: Port configuration file/preset: ${PORT_CONFIG}")

  # Verify that target port is supported
  set(PORT_CMAKE_PATH "${TI_BASE_PATH}/port/${PORT}/port.cmake")
  if(NOT EXISTS "${PORT_CMAKE_PATH}")
    message(NOTICE "TITAN: Target port not supported: ${PORT}.")
    message(NOTICE "TITAN: List of supported ports:")
    file(GLOB PORTS "${TI_BASE_PATH}/port/*")
    foreach(PORT_PATH ${PORTS})
      get_filename_component(PORT ${PORT_PATH} NAME)
      message(NOTICE " - ${PORT}")
    endforeach()
    message("")
    message(FATAL_ERROR "")
  endif()

  # Include port cmake file and create port library
  include("${PORT_CMAKE_PATH}")
  set(PORT_LIB_NAME "${LIB_NAME}_${PORT}")
  _ti_create_port_lib("${LIB_NAME}" "${PORT_LIB_NAME}" "${PORT_CONFIG}")

  # Get library configuration preset if applicable
  if(NOT EXISTS "${LIB_CONFIG}")
    string(TOLOWER "${LIB_CONFIG}" LIB_PRESET_NAME)
    set(LIB_PRESET_PATH "${TI_LIB_CONFIG_PRESET_DIR}/${LIB_PRESET_NAME}_config.json")
    if(NOT EXISTS "${LIB_PRESET_PATH}")
      message(NOTICE "TITAN: Invalid library configuration path/preset: ${LIB_CONFIG}.")
      message(NOTICE "TITAN: List of valid preset names:")
      file(GLOB LIB_PRESETS "${TI_LIB_CONFIG_PRESET_DIR}/*_config.json")
      foreach(PRESET ${LIB_PRESETS})
        get_filename_component(PRESET_FILE_NAME ${PRESET} NAME_WE)
        string(REGEX REPLACE "_config$" "" PRESET_NAME "${PRESET_FILE_NAME}")
        message(NOTICE " - ${PRESET_NAME}")
      endforeach()
      message("")
      message(FATAL_ERROR "")
    endif()
    set(LIB_CONFIG "${LIB_PRESET_PATH}")
  endif()

  # Initialize internal top-level interface library and link to port library.
  add_library("I_${LIB_NAME}" INTERFACE)
  _ti_parse_lib_config_file("${LIB_CONFIG}" LIB_CFG_DEF_LIST)
  target_compile_definitions("I_${LIB_NAME}" INTERFACE ${LIB_CFG_DEF_LIST})
  target_compile_definitions("I_${LIB_NAME}" INTERFACE "TI_PORT_${PORT}")
  target_include_directories("I_${LIB_NAME}" INTERFACE "${TI_BASE_PATH}/include")
  target_link_libraries("I_${LIB_NAME}" INTERFACE "${PORT_LIB_NAME}")

  # Initialize external top-level library.
  # Not this is required to wrap linker flags for library...
  add_library("${LIB_NAME}" INTERFACE)
  set(TI_WHOLE_ARCHIVE_ID_LIST "GNU" "Clang" "ARMClang" "TIClang")
  if("${CMAKE_C_COMPILER_ID}" IN_LIST TI_WHOLE_ARCHIVE_ID_LIST)
    message(DEBUG "TITAN: Applying 'whole-archive' flag to library: ${LIB_NAME}")
    target_link_libraries("${LIB_NAME}" INTERFACE 
      "-Wl,--whole-archive" "I_${LIB_NAME}" "-Wl,--no-whole-archive")
  else()
    target_link_libraries("${LIB_NAME}" INTERFACE "I_${LIB_NAME}")
  endif()

  # Display completion message, if debug display configuration details
  message(STATUS "TITAN: Configuration of ${LIB_NAME} complete.")
  get_property(LIB_COMPILE_FLAGS TARGET "${LIB_NAME}" PROPERTY TARGET_COMPILE_OPTIONS)
  get_property(LIB_LINK_FLAGS TARGET "${LIB_NAME}" PROPERTY TARGET_LINK_OPTIONS)
  message(DEBUG "TITAN: Library compiler flags: ${LIB_COMPILE_FLAGS}")
  message(DEBUG "TITAN: Library linker flags: ${LIB_LINK_FLAGS}")
endfunction()

# Build test target (if enabled)
if(TITAN_TEST_TARGET)
  message(STATUS "TITAN: Configuring test target...")
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test")
  message(STATUS "TITAN: Configuration of test target complete.")
endif()

# Build dev target (if enabled and present)
if(TITAN_DEV_TARGET)
  set(TI_DEV_DIR "${CMAKE_CURRENT_LIST_DIR}/dev")
  if(EXISTS "${TI_DEV_DIR}/CMakeLists.txt")
    message(STATUS "TITAN: Configuring dev target...")
    add_subdirectory("${TI_DEV_DIR}")
    message(STATUS "TITAN: Configuration of dev target complete.")
  else()
    message("TITAN: Skipping configuration of dev target. No dev directory found.")
  endif()
endif()