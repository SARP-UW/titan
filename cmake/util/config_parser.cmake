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
# @internal
# @file cmake/util/config_parser.cmake
# @authors Aaron McBride
# @brief Configuration parser utility for build system.

# CMake version/includes
cmake_minimum_required(VERSION 3.19)

# Recursive implementation of parse_config_file
function(_parse_config_file DEFINITION_LIST PREFIX JSON_STRING)
  set(TMP_DEF_LIST)
  file(JSON TYPE ${JSON_STRING} TYPE)
  if(TYPE STREQUAL "OBJECT")
    file(JSON KEYS ${JSON_STRING} KEY_LIST)
    foreach(CUR_KEY IN LISTS KEY_LIST)
      file(JSON GET ${JSON_STRING} ${CUR_KEY} KEY_VALUE)
      if(PREFIX STREQUAL "")
        set(DEF_NAME ${CUR_KEY})
      else()
        set(DEF_NAME "${PREFIX}_${CUR_KEY}")
      endif()
      file(JSON TYPE KEY_VALUE CHILD_TYPE)
      if(CHILD_TYPE STREQUAL "OBJECT" OR CHILD_TYPE STREQUAL "ARRAY")
        _parse_config_file(CHILD_LIST ${DEF_NAME} KEY_VALUE)
        list(APPEND TMP_DEF_LIST ${CHILD_LIST})
      else()
        if(CHILD_TYPE STREQUAL "STRING")
          if(NOT KEY_VALUE STREQUAL "")
            set(NEW_DEF "${DEF_NAME}_${KEY_VALUE}")
            list(APPEND TMP_DEF_LIST "${NEW_DEF}")
          endif()
        elseif(CHILD_TYPE STREQUAL "BOOLEAN")
          if(KEY_VALUE STREQUAL "ON")
            list(APPEND TMP_DEF_LIST "${DEF_NAME}=true")
          else()
            list(APPEND TMP_DEF_LIST "${DEF_NAME}=false")
          endif()
        elseif(CHILD_TYPE STREQUAL "NUMBER")
          list(APPEND TMP_DEF_LIST "${DEF_NAME}=${KEY_VALUE}")
        endif()
      endif()
    endforeach()
  elseif(TYPE STREQUAL "ARRAY")
    file(JSON LENGTH ${JSON_STRING} ARRAY_LENGTH)
    math(EXPR LAST_IDX "${ARRAY_LENGTH} - 1")
    foreach(i RANGE 0 ${LAST_IDX})
      file(JSON GET ${JSON_STRING} ${i} ELEM)
      set(DEF_NAME "${PREFIX}_${i}")
      file(JSON TYPE ELEM ELEM_TYPE)
      if(ELEM_TYPE STREQUAL "OBJECT" OR ELEM_TYPE STREQUAL "ARRAY")
        _parse_config_file(CHILD_LIST ${DEF_NAME} ELEM)
        list(APPEND TMP_DEF_LIST ${CHILD_LIST})
      else()
        if(ELEM_TYPE STREQUAL "STRING")
          if(NOT ELEM STREQUAL "")
            set(NEW_DEF "${DEF_NAME}_${ELEM}")
            list(APPEND TMP_DEF_LIST "${NEW_DEF}")
          endif()
        elseif(ELEM_TYPE STREQUAL "BOOLEAN")
          if(ELEM STREQUAL "ON")
            list(APPEND TMP_DEF_LIST "${DEF_NAME}=true")
          else()
            list(APPEND TMP_DEF_LIST "${DEF_NAME}=false")
          endif()
        elseif(ELEM_TYPE STREQUAL "NUMBER")
          list(APPEND TMP_DEF_LIST "${DEF_NAME}=${ELEM}")
        endif()
      endif()
    endforeach()
  else()
    if(TYPE STREQUAL "STRING")
      if(NOT JSON_STRING STREQUAL "")
        set(NEW_DEF "${PREFIX}_${JSON_STRING}")
        list(APPEND TMP_DEF_LIST "${NEW_DEF}")
      endif()
    elseif(TYPE STREQUAL "BOOLEAN")
      if(JSON_STRING STREQUAL "ON")
        list(APPEND TMP_DEF_LIST "${PREFIX}=true")
      else()
        list(APPEND TMP_DEF_LIST "${PREFIX}=false")
      endif()
    elseif(TYPE STREQUAL "NUMBER")
      list(APPEND TMP_DEF_LIST "${PREFIX}=${JSON_STRING}")
    endif()
  endif()
  set(${DEFINITION_LIST} "${TMP_DEF_LIST}" PARENT_SCOPE)
endfunction()

# Parses a titan library configuration file (JSON) and
# returns a list of definitions to pass to target_compile_definitions
function(parse_lib_config RESULT JSON_FILE_PATH)
  if(JSON_FILE_PATH NOT STREQUAL "NULL")
    file(READ ${JSON_FILE_PATH} JSON_STRING)
    _parse_config_file(${RESULT} "TI_LCFG" ${JSON_STRING})
  else()
    set(RESULT "")
  endif()
endfunction()

# Parses a titan port configuration file (JSON) and
# returns a list of definitions to pass to target_compile_definitions
function(parse_port_config RESULT JSON_FILE_PATH)
  if(JSON_FILE_PATH NOT STREQUAL "NULL")
    file(READ ${JSON_FILE_PATH} JSON_STRING)
    _parse_config_file(${RESULT} "TI_PCFG" ${JSON_STRING})
  else()
    set(RESULT "")
  endif()
endfunction()

