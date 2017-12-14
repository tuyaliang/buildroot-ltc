cmake_minimum_required(VERSION 2.8)

find_package(GTest REQUIRED) # to have GTEST_PREFIX and GTEST_INSTALL_DIR

include(ExternalProject)

set(GTEST_RELEASE 1.6.0)
set(GTEST_MD5 4577b49f2973c90bf9ba69aa8166b786)
set(GTEST_URL ${GTEST_PREFIX}/gtest-${GTEST_RELEASE}.zip)
set(GTEST_DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/libraries/gtest/download)
set(GTEST_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libraries/gtest/source)
set(GTEST_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libraries/gtest)

# GTEST_INSTALL_DIR is defined in FindGTest.cmake
set(GTEST_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR})
#set(GTEST_CMAKE_ARGS ${GTEST_CMAKE_ARGS} -DSKIP_INSTALL_FILES:BOOL=ON)
set(GTEST_PATCH_COMMAND "")
set(GTEST_CMAKE_CACHE_ARGS "")

#
# WARNING: Gtest was never cross compiler
# WARNING: Gtest was never compiled on MINGW (i.e. cygwin) nor android nor darwin
#
message(STATUS "external gtest")

if(MSVC)
  # Force /MT and /MTd
  set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS}
	-DCMAKE_C_FLAGS_DEBUG:STRING=${CMAKE_C_FLAGS_DEBUG} "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1"
	-DCMAKE_C_FLAGS_MINSIZEREL:STRING=${CMAKE_C_FLAGS_MINSIZEREL} "/MT /O1 /Ob1 /D NDEBUG"
	-DCMAKE_C_FLAGS_RELEASE:STRING=${CMAKE_C_FLAGS_RELEASE} "/MT /O2 /Ob2 /D NDEBUG"
	-DCMAKE_C_FLAGS_RELWITHDEBINFO:STRING=${CMAKE_C_FLAGS_RELWITHDEBINFO} "/MT /Zi /O2 /Ob1 /D NDEBUG"

	-DCMAKE_CXX_FLAGS_DEBUG:STRING=${CMAKE_CXX_FLAGS_DEBUG} "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1"
	-DCMAKE_CXX_FLAGS_MINSIZEREL:STRING=${CMAKE_CXX_FLAGS_MINSIZEREL} "/MT /O1 /Ob1 /D NDEBUG"
	-DCMAKE_CXX_FLAGS_RELEASE:STRING=${CMAKE_CXX_FLAGS_RELEASE} "/MT /O2 /Ob2 /D NDEBUG"
	-DCMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING=${CMAKE_CXX_FLAGS_RELWITHDEBINFO} "/MT /Zi /O2 /Ob1 /D NDEBUG"
  )
  
  # Force /MACHINE
  set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} -DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS})
  set(GTEST_PATCH_COMMAND cmake -E chdir . ${GTEST_PREFIX}/patch/win32/CMakeListsPatch.bat)
else()
  # use unified diff format
  set(GTEST_PATCH_COMMAND cmake -E chdir <SOURCE_DIR> patch -p0 -i ${GTEST_PREFIX}/patch/unified/CMakeLists.patch)
endif()

if(MINGW) 
  set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} 
	-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
	-DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS}
	-DCMAKE_SHARED_LINKER_FLAGS:STRING=${CMAKE_SHARED_LINKER_FLAGS}
	-DCMAKE_SHARED_MODULE_FLAGS:STRING=${CMAKE_MODULE_LINKER_FLAGS}
  )
endif()

if(ANDROID)
  set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS}
	-DANDROID_TARGET_PRODUCT:STRING=${ANDROID_TARGET_PRODUCT}
	-DANDROID_TARGET_OUT:STRING=${ANDROID_TARGET_OUT}
	-DANDROID_ROOT:STRING=${ANDROID_ROOT}
  )
endif()
  
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

  if(${FORCE_32BIT_BUILD} MATCHES "ON")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} -DFORCE_32BIT_BUILD:BOOL=ON)
  endif()
  
  set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS}
	-DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS}
	-DCMAKE_SHARED_LINKER_FLAGS:STRING=${CMAKE_SHARED_LINKER_FLAGS}

	-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
  )

endif()

# Pass toolchain
if(NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
  set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} -DCMAKE_TOOLCHAIN_FILE:STRING=${CMAKE_TOOLCHAIN_FILE})
endif()

# Need to set the build type
set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE})

# Pass any non default configuration
if(CMAKE_CONFIGURATION_TYPES)
  foreach(CONFIG_NAME ${CMAKE_CONFIGURATION_TYPES})
    if(NOT "${CONFIG_NAME}" STREQUAL "Debug" AND
       NOT "${CONFIG_NAME}" STREQUAL "Release" AND
       NOT "${CONFIG_NAME}" STREQUAL "MinSizeRel" AND
       NOT "${CONFIG_NAME}" STREQUAL "RelWithDebInfo")

      string(TOUPPER ${CONFIG_NAME} CONFIG_NAME)
      #Set the flags for this configuration
      foreach(FLAGS_NAME CXX_FLAGS C_FLAGS) #Compiler flags
        set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} -DCMAKE_${FLAGS_NAME}_${CONFIG_NAME}:STRING=${CMAKE_${FLAGS_NAME}_${CONFIG_NAME}})
      endforeach()
      
      foreach(FLAGS_NAME EXE_LINKER_FLAGS MODULE_LINKER_FLAGS SHARED_LINKER_FLAGS) #Linker flags
        set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} -DCMAKE_${FLAGS_NAME}_${CONFIG_NAME}:STRING=${CMAKE_${FLAGS_NAME}_${CONFIG_NAME}})
      endforeach()
    endif()
  endforeach()

  set(GTEST_CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS} -DCMAKE_CONFIGURATION_TYPES:STRING=${CMAKE_CONFIGURATION_TYPES})
endif()

# Copy CMakeList.txt and cmakeconfig.h.in to source directory
# use for future patch
#set(GTEST_PATCH_COMMAND cmake -E copy_directory ${GTEST_PREFIX}/patch <SOURCE_DIR>)

if ( CMAKE_VERSION VERSION_GREATER "2.8.3" )
  # ExternalProject_Add has CMAKE_CACHE_ARGS and URL_MD5
  ExternalProject_Add(
    ${GTEST_NAME}
    URL ${GTEST_URL}
    URL_MD5 ${GTEST_MD5}
    DOWNLOAD_DIR ${GTEST_DOWNLOAD_DIR}
    SOURCE_DIR ${GTEST_SOURCE_DIR}
    BINARY_DIR ${GTEST_BINARY_DIR}
    INSTALL_DIR ${GTEST_INSTALL_DIR}
    CMAKE_ARGS ${GTEST_CMAKE_ARGS}
    CMAKE_CACHE_ARGS ${GTEST_CMAKE_CACHE_ARGS}
    UPDATE_COMMAND ""
    PATCH_COMMAND ${GTEST_PATCH_COMMAND}
  )
elseif( CMAKE_VERSION VERSION_GREATER "2.8.1" )
  # ExternalProject_Add has URL_MD5
  # CMAKE_CACHE_ARGS option in ExternalProject_Add is only implemented in
  # cmake starting in version 2.8.4. Use CMAKE_ARGS for now (this limits
  # the max command line to 8k chars on windows).
  set(GTEST_CMAKE_ARGS ${GTEST_CMAKE_ARGS} ${GTEST_CMAKE_CACHE_ARGS})
  
  ExternalProject_Add(
    ${GTEST_NAME}
    URL ${GTEST_URL}
    URL_MD5 ${GTEST_MD5}
    DOWNLOAD_DIR ${GTEST_DOWNLOAD_DIR}
    SOURCE_DIR ${GTEST_SOURCE_DIR}
    BINARY_DIR ${GTEST_BINARY_DIR}
    INSTALL_DIR ${GTEST_INSTALL_DIR}
    CMAKE_ARGS ${GTEST_CMAKE_ARGS}
    UPDATE_COMMAND ""
    PATCH_COMMAND ${GTEST_PATCH_COMMAND}
  )
else()
  # CMAKE_CACHE_ARGS option in ExternalProject_Add is only implemented in
  # cmake starting in version 2.8.4. Use CMAKE_ARGS for now (this limits
  # the max command line to 8k chars on windows).
  set(GTEST_CMAKE_ARGS ${GTEST_CMAKE_ARGS} ${GTEST_CMAKE_CACHE_ARGS})
  
  ExternalProject_Add(
    ${GTEST_NAME}
    URL ${GTEST_URL}
    DOWNLOAD_DIR ${GTEST_DOWNLOAD_DIR}
    SOURCE_DIR ${GTEST_SOURCE_DIR}
    BINARY_DIR ${GTEST_BINARY_DIR}
    INSTALL_DIR ${GTEST_INSTALL_DIR}
    CMAKE_ARGS ${GTEST_CMAKE_ARGS}
    UPDATE_COMMAND ""
    PATCH_COMMAND ${GTEST_PATCH_COMMAND}
  )
endif()
