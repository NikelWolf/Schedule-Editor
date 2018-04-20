cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(mirea_schedule VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)

option(DEV_BUILD ON) # if build dev than windows will have console on sturtup and schedule template will be copied into build folder

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

if (WIN32 AND DEV_BUILD)
    add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
include_directories(${XLNT_HomeDir}/include)
target_link_libraries(${PROJECT_NAME} xlnt)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Sql)

configure_file(${RESOURCES_DIR}/schedule_default_template.xlsx ${CMAKE_BINARY_DIR}/jstf.dat COPYONLY)

if (DEV_BUILD)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${CMAKE_BINARY_DIR}/resources)
endif()

if (WIN32)
    set(QT_BIN_VERSION_PATH C:/Qt/5.10.0/mingw53_32/bin)
    set(dll_file
                ${CMAKE_BINARY_DIR}/third-party/xlnt/source/libxlntd.dll

                ${QT_BIN_VERSION_PATH}/Qt5Cored.dll
                ${QT_BIN_VERSION_PATH}/Qt5Widgetsd.dll
                ${QT_BIN_VERSION_PATH}/Qt5Guid.dll

                ${QT_BIN_VERSION_PATH}/libgcc_s_dw2-1.dll
                ${QT_BIN_VERSION_PATH}/libstdc++-6.dll
                ${QT_BIN_VERSION_PATH}/libwinpthread-1.dll )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${dll_file} ${CMAKE_BINARY_DIR})
endif()