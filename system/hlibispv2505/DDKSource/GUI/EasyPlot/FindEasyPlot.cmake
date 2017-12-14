cmake_minimum_required (VERSION 3.2)

get_filename_component (EASYPLOT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)

set (EASYPLOT_FOUND TRUE)
set (EASYPLOT_INCLUDE_DIRS ${EASYPLOT_PREFIX}/include/)
set (EASYPLOT_DEFINES)
set (EASYPLOT_NAME EasyPlot)
set (EASYPLOT_LIBRARIES ${EASYPLOT_NAME})
