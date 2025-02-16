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
# @file port/STM32H745/buildsys/settings.cmake
# @authors Aaron McBride
# @brief Cmake file for the STM32H745 port.
# @todo Verify target configuration for ICC-like compilers.

cmake_minimum_required(VERSION 3.19)
include("${CMAKE_CURRENT_LIST_DIR}/../../common/cmake/config_parser.cmake")

# Declare relative path variables for use in functions
set(TI_PORT_BASE_PATH "${CMAKE_CURRENT_LIST_DIR}")
set(TI_PORT_CONFIG_PRESET_DIR "${TI_PORT_BASE_PATH}/port_config")

# INTERNAL - Creates interface library for the STM32H745 port.
function(_ti_create_port_lib LIB_NAME PORT_LIB_NAME PORT_CONFIG)
  message(DEBUG "TITAN: Configuring port library ${PORT_LIB_NAME}...")

  # Get port configuration file preset if applicable
  if(NOT EXISTS "${PORT_CONFIG}")
    string(TOLOWER "${PORT_CONFIG}" PORT_PRESET_NAME)
    set(PORT_PRESET_PATH "${TI_PORT_CONFIG_PRESET_DIR}/${PORT_PRESET_NAME}_config.json")
    if(NOT EXISTS "${PORT_PRESET_PATH}")
      message(NOTICE "TITAN: Invalid port configuration path/preset: ${PORT_CONFIG}.")
      message(NOTICE "TITAN: List of valid preset names for port configuration:")
      file(GLOB PORT_PRESETS "${TI_PORT_CONFIG_PRESET_DIR}/*_config.json")
      foreach(PRESET ${PORT_PRESETS})
        get_filename_component(PRESET_FILE_NAME ${PRESET} NAME_WE)
        string(REGEX REPLACE "_config.json$" "" PRESET_NAME ${PRESET_FILE_NAME})
        message(NOTICE " - ${PRESET_NAME}")
      endforeach()
      message("")
      message(FATAL_ERROR "")
    endif()
    set(PORT_CONFIG "${PORT_PRESET_PATH}")
  endif()

  # Initialize port library target 
  add_library("${PORT_LIB_NAME}" INTERFACE "${LIB_SOURCES}")
  _ti_parse_port_config_file("${PORT_CONFIG}" PORT_CFG_DEF_LIST)
  target_compile_definitions("${PORT_LIB_NAME}" INTERFACE ${PORT_CFG_DEF_LIST})
  target_include_directories("${PORT_LIB_NAME}" INTERFACE "${TI_PORT_BASE_PATH}/include")
  target_include_directories("${PORT_LIB_NAME}" INTERFACE "${TI_PORT_BASE_PATH}/src")

  # Add sources to port library target
  set(TI_PORT_SRC_DIR "${TI_PORT_BASE_PATH}/src/STM32H745")
  file(GLOB_RECURSE LIB_SOURCES "${TI_PORT_SRC_DIR}/*.h" "${TI_PORT_SRC_DIR}/*.c")
  target_sources("${PORT_LIB_NAME}" INTERFACE ${LIB_SOURCES})
  
  # Lists of compiler IDs which share configuration settings (for port library)
  set(TI_PORT_GNU_ID_LIST "GNU" "Clang" "ARMClang" "TIClang")
  set(TI_PORT_ICC_ID_LIST "ICC" "IAR" "ARMCC" "TI")

  # Set compiler/linker flags for GNU-like compilers
  if("${CMAKE_C_COMPILER_ID}" IN_LIST TI_PORT_GNU_ID_LIST)
    message(DEBUG "TITAN: Using GNU compiler configuration for port.")
    target_compile_options("${PORT_LIB_NAME}" INTERFACE
      "-mcpu=cortex-m4" "-mthumb" "-mfpu=fpv4-sp-d16")
    target_link_options("${PORT_LIB_NAME}" INTERFACE
      "-T${TI_PORT_BASE_PATH}/linker_scripts/gnu_link.ld"
      "-mcpu=cortex-m4" "-mthumb" "-mfpu=fpv4-sp-d16")

  # Set compiler/linker flags for ICC-based compilers
  elseif("${CMAKE_C_COMPILER_ID}" IN_LIST TI_PORT_ICC_ID_LIST)
    message(DEBUG "TITAN: Using ICC compiler configuration for port.")
    target_compile_options("${PORT_LIB_NAME}" INTERFACE
      "--cpu=Cortex-M4" "--thumb" "--fpu=FPv4-SP-D16")
    target_link_options("${PORT_LIB_NAME}" INTERFACE
      "--config ${TI_PORT_BASE_PATH}/linker_scripts/icc_link.icf"
      "--cpu=Cortex-M4" "--thumb" "--fpu=FPv4-SP-D16")

  else() # Error on unsupported compiler.
    message(NOTICE "TITAN: Unsupported compiler: ${CMAKE_C_COMPILER_ID}.")
    message(NOTICE "TITAN: List of supported compilers for port:")
    foreach(COMPILER_ID IN LISTS ${TI_PORT_GNU_ID_LIST} ${TI_PORT_ICC_ID_LIST})
      message(NOTICE " - ${COMPILER_ID}")
    endforeach()
    message("")
    message(FATAL_ERROR "")
  endif()
endfunction()