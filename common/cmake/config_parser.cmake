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
# @file cmake/util/config_parser.cmake
# @authors Aaron McBride
# @brief Facilities for parsing configuration files.

cmake_minimum_required(VERSION 3.19)

# INTERNAL
# Function to split top-level JSON objects and arrays
# INPUT_STR: (string) JSON text to split
# OUTPUT_LIST: (list) Output list of top-level JSON objects and arrays
function(_ti_split_top_level INPUT_STR OUTPUT_LIST)
  set(RESULT "")
  set(CURRENT "")
  string(LENGTH "${INPUT_STR}" LEN)
  set(LEVEL 0)
  math(EXPR LEN_MINUS_ONE "${LEN} - 1")
  
  # Iterate over each character to detect top-level commas as separators.
  foreach(I RANGE 0 ${LEN_MINUS_ONE})
    string(SUBSTRING "${INPUT_STR}" ${I} 1 CH)
    
    # Track nesting level
    if(CH STREQUAL "{" OR CH STREQUAL "[")
      math(EXPR LEVEL "${LEVEL} + 1")
    elseif(CH STREQUAL "}" OR CH STREQUAL "]")
      math(EXPR LEVEL "${LEVEL} - 1")
    endif()
    
    # Split on top-level commas
    if(CH STREQUAL "," AND LEVEL EQUAL 0)
      string(STRIP "${CURRENT}" CURRENT_STR)
      list(APPEND RESULT "${CURRENT_STR}")
      set(CURRENT "")
    else()
      set(CURRENT "${CURRENT}${CH}")
    endif()
  endforeach()
  
  # Append the final token if present.
  string(STRIP "${CURRENT}" CURRENT_STR)
  if(NOT CURRENT_STR STREQUAL "")
    list(APPEND RESULT "${CURRENT_STR}")
  endif()
  set(${OUTPUT_LIST} "${RESULT}" PARENT_SCOPE)
endfunction()

# INTERNAL
# Recursively process JSON text into CMake definitions
# JSON_TEXT: (string) JSON text to process
# PREFIX: (string) Prefix for CMake definitions
# MACRO_DEFS: (list) Output list of CMake definitions
function(_ti_process_json JSON_TEXT PREFIX MACRO_DEFS)
  string(STRIP "${JSON_TEXT}" JSON_TEXT)

  # Handle JSON object
  if(JSON_TEXT MATCHES "^\\{.*\\}$")
    string(REGEX REPLACE "^[[:space:]]*\\{" "" JSON_TEXT "${JSON_TEXT}")
    string(REGEX REPLACE "\\}[[:space:]]*$" "" JSON_TEXT "${JSON_TEXT}")
    _ti_split_top_level("${JSON_TEXT}" ENTRIES)
    foreach(ENTRY IN LISTS ENTRIES)
      string(STRIP "${ENTRY}" ENTRY)

      # Expecting: "key" : value
      string(REGEX MATCH "^\"([^\"]+)\"[[:space:]]*:[[:space:]]*(.*)$" _MATCH "${ENTRY}")
      if(NOT _MATCH)
        message(WARNING "Skipping unrecognized object in config file: ${ENTRY}")
        continue()
      endif()
      set(KEY "${CMAKE_MATCH_1}")
      set(VAL "${CMAKE_MATCH_2}")
      string(TOUPPER "${KEY}" KEY_UC)
      if("${PREFIX}" STREQUAL "")
        set(NEW_PREFIX "${KEY_UC}")
      else()
        set(NEW_PREFIX "${PREFIX}_${KEY_UC}")
      endif()

      # Recurse if value is an object or array
      if(VAL MATCHES "^[[:space:]]*\\{.*\\}[[:space:]]*$" OR VAL MATCHES "^[[:space:]]*\\[.*\\][[:space:]]*$")
        _ti_process_json("${VAL}" "${NEW_PREFIX}" MACRO_DEFS)
      elseif(VAL MATCHES "^[[:space:]]*\".*\"[[:space:]]*$")
        string(REGEX REPLACE "^[[:space:]]*\"(.*)\"[[:space:]]*$" "\\1" STR_VAL "${VAL}")
        set(MACRO_NAME "${NEW_PREFIX}_${STR_VAL}")
        list(APPEND MACRO_DEFS "-D${MACRO_NAME}")
      else()
        list(APPEND MACRO_DEFS "-D${NEW_PREFIX}=${VAL}")
      endif()
    endforeach()

  # Handle JSON array
  elseif(JSON_TEXT MATCHES "^\\[.*\\]$")
    string(REGEX REPLACE "^[[:space:]]*\\[" "" JSON_TEXT "${JSON_TEXT}")
    string(REGEX REPLACE "\\][[:space:]]*$" "" JSON_TEXT "${JSON_TEXT}")
    _ti_split_top_level("${JSON_TEXT}" ELEMENTS)
    set(IDX 0)
    foreach(ELEMENT IN LISTS ELEMENTS)
      string(STRIP "${ELEMENT}" ELEMENT)
      set(NEW_PREFIX "${PREFIX}_${IDX}")
      if(ELEMENT MATCHES "^[[:space:]]*\\{.*\\}[[:space:]]*$" OR ELEMENT MATCHES "^[[:space:]]*\\[.*\\][[:space:]]*$")
        _ti_process_json("${ELEMENT}" "${NEW_PREFIX}" MACRO_DEFS)
      elseif(ELEMENT MATCHES "^[[:space:]]*\".*\"[[:space:]]*$")
        string(REGEX REPLACE "^[[:space:]]*\"(.*)\"[[:space:]]*$" "\\1" STR_VAL "${ELEMENT}")
        set(MACRO_NAME "${NEW_PREFIX}_${STR_VAL}")
        list(APPEND MACRO_DEFS "-D${MACRO_NAME}")
      else()
        list(APPEND MACRO_DEFS "-D${NEW_PREFIX}=${ELEMENT}")
      endif()
      math(EXPR IDX "${IDX} + 1")
    endforeach()
    
  # Base literal value
  else()
    string(STRIP "${JSON_TEXT}" JSON_TEXT)
    if(JSON_TEXT MATCHES "^\".*\"$")
      string(REGEX REPLACE "^\"(.*)\"$" "\\1" STR_VAL "${JSON_TEXT}")
      set(MACRO_NAME "${PREFIX}_${STR_VAL}")
      list(APPEND MACRO_DEFS "-D${MACRO_NAME}")
    else()
      list(APPEND MACRO_DEFS "-D${PREFIX}=${JSON_TEXT}")
    endif()
  endif()
  set(${MACRO_DEFS} "${MACRO_DEFS}" PARENT_SCOPE)
endfunction()

# Parse a JSON configuration file into CMake definitions
# JSON_FILE: Path to the JSON configuration file
# OUT_DEF_LIST: Output list of CMake definitions
function(ti_parse_config_file JSON_FILE OUT_DEF_LIST)
  file(READ "${JSON_FILE}" JSON_TEXT)
  string(REPLACE "\n" " " JSON_TEXT "${JSON_TEXT}")
  set(MACRO_DEFS "")
  _ti_process_json("${JSON_TEXT}" "" MACRO_DEFS)
  set(${OUT_DEF_LIST} "${MACRO_DEFS}" PARENT_SCOPE)
endfunction()