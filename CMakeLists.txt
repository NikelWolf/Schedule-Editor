cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(mirea_schedule VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include(ExternalProject)
find_package(Git REQUIRED)

set(XLNT_INSTALL_LOCATION ${CMAKE_BINARY_DIR})
set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/sources/src)

ExternalProject_Add(xlntlib
    GIT_REPOSITORY https://github.com/tfussell/xlnt
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${XLNT_INSTALL_LOCATION} -DSTATIC=ON -DTESTS=OFF -DSAMPLES=OFF -DBENCHMARKS=OFF -DPYTHON=OFF
)

include_directories(${XLNT_INSTALL_LOCATION}/include)
link_directories(${XLNT_INSTALL_LOCATION}/lib)

add_executable(${PROJECT_NAME} ${SOURCES_DIR}/main.cpp)
add_dependencies(${PROJECT_NAME} xlntlib)
target_link_libraries(${PROJECT_NAME} xlnt)
