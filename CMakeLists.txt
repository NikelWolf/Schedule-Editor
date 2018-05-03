cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(mirea_schedule VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)

# if build dev than windows will have console on sturtup
# and schedule template will be copied into build folder
set(DEV_BUILD TRUE)

add_subdirectory(sources/scheduler)

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/sources/source)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/sources/resources)

set(SOURCES
        ${SOURCES_DIR}/main.cpp
        )

if (WIN32 AND DEV_BUILD)
    add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scheduler/include)
target_link_libraries(${PROJECT_NAME} scheduler)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Sql)

if (DEV_BUILD)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${CMAKE_BINARY_DIR}/resources)
endif()

if (WIN32)
    set(QT_BIN_VERSION_PATH ${Qt5Core_DIR}/../../../bin)
    set(dll_file
            # Qt libraries
                ${QT_BIN_VERSION_PATH}/Qt5Cored.dll
                ${QT_BIN_VERSION_PATH}/Qt5Widgetsd.dll
                ${QT_BIN_VERSION_PATH}/Qt5Guid.dll

            # MinGW libraries
                ${QT_BIN_VERSION_PATH}/libgcc_s_dw2-1.dll
                ${QT_BIN_VERSION_PATH}/libstdc++-6.dll
                ${QT_BIN_VERSION_PATH}/libwinpthread-1.dll
            )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${dll_file} ${CMAKE_BINARY_DIR})
endif()
