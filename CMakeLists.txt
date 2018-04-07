cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(mirea_schedule VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#include(ExternalProject)
#find_package(Git REQUIRED)

set(XLNT_HomeDir ${CMAKE_SOURCE_DIR}/third-party/xlnt)
add_subdirectory(${XLNT_HomeDir})
if (WIN32)
    set_property(TARGET xlnt PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/third-party/XLNT/source/libxlntd.dll)
elseif(UNIX)
    set_property(TARGET xlnt PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/third-party/XLNT/source/libxlntd.so)
endif()


set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/sources/source)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/sources/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/sources/resources)


set(SOURCES ${SOURCES_DIR}/main.cpp
            ${SOURCES_DIR}/common.cpp
            ${SOURCES_DIR}/schedule_error.cpp
            ${SOURCES_DIR}/lesson.cpp
            ${SOURCES_DIR}/xlsx_file.cpp
            ${SOURCES_DIR}/group_schedule.cpp
            ${SOURCES_DIR}/scheduler.cpp )


set(HEADERS ${INCLUDE_DIR}/common.h
            ${INCLUDE_DIR}/schedule_error.h
            ${INCLUDE_DIR}/lesson.h
            ${INCLUDE_DIR}/xlsx_file.h
            ${INCLUDE_DIR}/group_schedule.h
            ${INCLUDE_DIR}/scheduler.h )
#
#
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
include_directories(${XLNT_HomeDir}/include)
target_link_libraries(${PROJECT_NAME} xlnt)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${CMAKE_BINARY_DIR}/resources)

if (WIN32)
    set(dll_file ${CMAKE_BINARY_DIR}/third-party/xlnt/source/libxlntd.dll)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${dll_file} ${CMAKE_BINARY_DIR})
endif()