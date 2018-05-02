cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(scheduler_api VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library type
option(STATIC "Set to ON to build scheduler as a static library instead of a shared library" OFF)

# Commonly used project directories
set(SCHEDULER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SCHEDULER_INCLUDE_DIR ${SCHEDULER_ROOT_DIR}/include)
set(SCHEDULER_SOURCE_DIR ${SCHEDULER_ROOT_DIR}/source)
set(SCHEDULER_RESOURCES_DIR ${SCHEDULER_ROOT_DIR}/resources)
set(THIRD_PARTY_DIR ${SCHEDULER_ROOT_DIR}/third-party)

# Include xlnt library
add_subdirectory(${THIRD_PARTY_DIR}/xlnt
        ${CMAKE_CURRENT_BINARY_DIR}/third-party/xlnt)

# Non-target-specific compiler settings
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4") # level 4 warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP") # multi-processor compilation
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # all warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra") # extra warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas") # ignore MSVC and Clang pragmas
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything") # all warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror") # warnings are errors
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat") # ignore warnings about C++98 compatibility
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic") # ignore pedantic warnings about C++98 compatibility
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded") # ignore padding warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-documentation-unknown-command") # ignore unknown commands in Javadoc-style comments
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas") # ignore Windows and GCC pragmas
endif ()

file(GLOB SCHEDULER_HEADERS ${SCHEDULER_INCLUDE_DIR}/*.h)
file(GLOB SCHEDULER_SOURCES ${SCHEDULER_SOURCE_DIR}/*.cpp)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # Set a default CMAKE_INSTALL_PREFIX if one wasn't specified

    set(DEFAULT_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed")

    # Apply the variable and save to cache
    set(CMAKE_INSTALL_PREFIX ${DEFAULT_INSTALL_PREFIX}
            CACHE PATH "default install path" FORCE)
endif ()

set(LIBRARY_NAME scheduler)
if (NOT STATIC)
    # Compile shared library
    add_library(${LIBRARY_NAME} SHARED
            ${SCHEDULER_HEADERS}
            ${SCHEDULER_SOURCES})
    add_dependencies(${LIBRARY_NAME} xlnt)

    # Set SO version (for symbolic links like libscheduler.so.1.2 and libscheduler.so.1)
    set_target_properties(${LIBRARY_NAME}
            PROPERTIES
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
else ()
    # Compile static library
    add_library(${LIBRARY_NAME} STATIC ${SCHEDULER_HEADERS} ${SCHEDULER_SOURCES})

    add_dependencies(${LIBRARY_NAME} xlnt)
endif ()

# Includes
target_include_directories(${LIBRARY_NAME} PUBLIC ${SCHEDULER_INCLUDE_DIR})
target_include_directories(${LIBRARY_NAME} PRIVATE ${SCHEDULER_SOURCE_DIR})
target_include_directories(${LIBRARY_NAME} PUBLIC ${THIRD_PARTY_DIR}/xlnt/include)
target_link_libraries(${LIBRARY_NAME} xlnt)

# Platform- and file-specific settings, MSVC
if (MSVC)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS=1)

    if (NOT STATIC)
        target_compile_definitions(${LIBRARY_NAME} PRIVATE SCHEDULER_EXPORT=1)
    endif ()

    set_target_properties(${LIBRARY_NAME} PROPERTIES
            COMPILE_FLAGS "/wd\"4251\" /wd\"4275\" /wd\"4068\"")
endif ()

# Configure resources files
configure_file(${SCHEDULER_RESOURCES_DIR}/schedule_default_template.xlsx
        ${CMAKE_BINARY_DIR}/jstf.dat COPYONLY)

if (WIN32)
    set(LIBS_END_POSTFIX "dll")
elseif (UNIX)
    set(LIBS_END_POSTFIX "so")
endif ()

add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/third-party/xlnt/source/libxlntd.${LIBS_END_POSTFIX}
        ${CMAKE_BINARY_DIR}/libxlntd.${LIBS_END_POSTFIX}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/libschedulerd.${LIBS_END_POSTFIX}
${CMAKE_BINARY_DIR}/libschedulerd.${LIBS_END_POSTFIX})
