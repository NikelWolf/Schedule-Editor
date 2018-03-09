cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(mirea_schedule VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include(ExternalProject)
find_package(Git REQUIRED)


set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/sources/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/sources/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/sources/resources)


set(XLNT_INSTALL_LOCATION ${CMAKE_BINARY_DIR})
ExternalProject_Add(xlntlib
    GIT_REPOSITORY https://github.com/tfussell/xlnt
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${XLNT_INSTALL_LOCATION} -DSTATIC=ON -DTESTS=OFF -DSAMPLES=OFF -DBENCHMARKS=OFF -DPYTHON=OFF
)
include_directories(${XLNT_INSTALL_LOCATION}/include)
link_directories(${XLNT_INSTALL_LOCATION}/lib)


add_executable(${PROJECT_NAME} ${SOURCES_DIR}/main.cpp ${INCLUDE_DIR}/schedule_parser.h ${SOURCES_DIR}/schedule_parser.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
add_dependencies(${PROJECT_NAME} xlntlib)
target_link_libraries(${PROJECT_NAME} xlnt)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${CMAKE_BINARY_DIR}/resources)