# Set toolchain name and path of binaries
set(TOOLCHAIN_NAME "arm_gnu_toolchain")
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_DIR}/${TOOLCHAIN_NAME}/bin)

# Determine if toolchain needs to be downloaded
if(NOT EXISTS TOOLCHAIN_BIN_DIR) 
  message(STATUS "Required toolchain not found in local cache.")

  # Get toolchain download link for windows
  if(CMAKE_HOST_WIN32)
    set(SYS_EXEC_SUFFIX ".exe")
    set(TOOLCHAIN_ARCHIVE_NAME "toolchain.zip")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "AMD64")
      set(TOOLCHAIN_LINK "https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-mingw-w64-i686-arm-none-eabi.zip")
    else()
      message(FATAL_ERROR "Required toolchain does not support host processor.")
    endif()  

  # Get toolchain download link for mac
  elseif(CMAKE_HOST_APPLE)
    set(SYS_EXEC_SUFFIX "")
    set(TOOLCHAIN_ARCHIVE_NAME "toolchain.tar.xz")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
      set(TOOLCHAIN_LINK "https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-darwin-x86_64-arm-none-eabi.tar.xz")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
      set(TOOLCHAIN_LINK "https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-darwin-arm64-arm-none-eabi.tar.xz")
    else()
      message(FATAL_ERROR "Required toolchain does not support host processor.")
    endif()

  # Get toolchain download link for linux
  elseif(CMAKE_HOST_UNIX)
    set(SYS_EXEC_SUFFIX "")
    set(TOOLCHAIN_ARCHIVE_NAME "toolchain.tar.xz")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
      set(TOOLCHAIN_LINK "https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi.tar.xz")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "aarch64" OR
        CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "aarch64_be" OR
        CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "armv8b" OR
        CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "armv8l")
      set(TOOLCHAIN_LINK "https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-aarch64-arm-none-eabi.tar.xz")
    else()
      message(FATAL_ERROR "Required toolchain does not support host processor.")
    endif()
  else()
    message(FATAL_ERROR "Required toolchain does not support host operating system.")
  endif()

  # Download toolchain
  message(STATUS "Downloading toolchain... Do not close process.")
  file(MAKE_DIRECTORY ${TEMP_DIR})
  set(TOOLCHAIN_ARCHIVE_PATH ${TEMP_DIR}/${TOOLCHAIN_ARCHIVE_NAME})
  file(DOWNLOAD ${TOOLCHAIN_LINK} ${TOOLCHAIN_ARCHIVE_PATH} SHOW_PROGRESS)

  # Extract toolchain
  message(STATUS "Extracting toolchain... Do not close process.")
  file(ARCHIVE_EXTRACT INPUT ${TOOLCHAIN_ARCHIVE_PATH} DESTINATION ${TOOLCHAIN_DIR})

  # Remove temp folder (toolchain download archive)
  message(STATUS "Removing toolchain archive... Do not close process.")
  file(REMOVE_RECURSE ${TEMP_DIR})

  # Find and normalize toolchain directory name -> arm_gnu_toolchain
  file(GLOB TOOLCHAIN_EXTRACT_DIR_LIST LIST_DIRECTORIES true 
      ${TOOLCHAIN_DIR}/arm-gnu-toolchain*arm-none-eabi)
  list(LENGTH TOOLCHAIN_EXTRACT_DIR_LIST EXTRACT_COUNT)
  if(NOT EXTRACT_COUNT EQUAL 0)
    list(GET TOOLCHAIN_EXTRACT_DIR_LIST 0 TOOLCHAIN_EXTRACT_DIR)
    file(RENAME ${TOOLCHAIN_EXTRACT_DIR} ${TOOLCHAIN_NAME})
  else()
    message(FATAL_ERROR "Toolchain extract directory could not be found")
  endif()
else()
  message(STATUS "Required toolchain found in local cache.")
endif()

# Register/set paths to compilers within toolchain
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-gcc${SYS_EXEC_SUFFIX})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-g++${SYS_EXEC_SUFFIX})
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-gcc${SYS_EXEC_SUFFIX})
set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-objcopy${SYS_EXEC_SUFFIX})
set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-objdump${SYS_EXEC_SUFFIX})
set(CMAKE_SIZE ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-size${SYS_EXEC_SUFFIX})

# Set target system/processor
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Set compiler config
set(CMAKE_EXE_LINKER_FLAGS_INIT "-nostdlib")

# Verify compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)