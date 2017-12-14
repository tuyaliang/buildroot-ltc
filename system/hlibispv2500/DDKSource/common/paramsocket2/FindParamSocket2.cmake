cmake_minimum_required (VERSION 2.8)

get_filename_component (PARAMSOCKET2_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)

set (PARAMSOCKET2_FOUND TRUE)
set (PARAMSOCKET2_INCLUDE_DIRS ${PARAMSOCKET2_PREFIX}/include/)
set (PARAMSOCKET2_DEFINES)
set (PARAMSOCKET2_NAME FelixParamSocket2)
set (PARAMSOCKET2_LIBRARIES ${PARAMSOCKET2_NAME})

