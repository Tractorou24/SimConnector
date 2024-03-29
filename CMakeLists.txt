﻿cmake_minimum_required(VERSION 3.25)

# Add our CMake modules files in the CMake path.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Enable folders for IDE projects generation (e.g Visual Studio)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Setup build type
include(SPARKBuildType)

project(SimConnector VERSION 0.1.0 LANGUAGES CXX)

# Set the C++ version used throughout the project
set(CMAKE_CXX_STANDARD 20)
# Enforce C++ standard as required for the compiler
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable C++ compiler extension (like gnu) to ensure portable code
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable CTest (and create variable BUILD_TESTING)
include(CTest)

# Define installation directories variables using GNU Standard.
include(GNUInstallDirs)

# Declare SPARK general options
option(BUILD_SHARED_LIBS "Build shared libraries. Static libraries otherwise" ON)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(SPARK_OUTPUT_DIR ${CMAKE_BINARY_DIR}/_output)

block()
    get_property(SPARK_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if (SPARK_IS_MULTI_CONFIG)
        # Setup build output directories
        foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
            string(TOUPPER ${TYPE} TYPE_UPPER)
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} ${SPARK_OUTPUT_DIR}/${TYPE}/${CMAKE_INSTALL_LIBDIR} PARENT_SCOPE)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} ${SPARK_OUTPUT_DIR}/${TYPE}/${CMAKE_INSTALL_LIBDIR} PARENT_SCOPE)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} ${SPARK_OUTPUT_DIR}/${TYPE}/${CMAKE_INSTALL_BINDIR} PARENT_SCOPE)
        endforeach()
    else()
        set(ARCHIVE_OUTPUT_DIRECTORY ${SPARK_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_INSTALL_LIBDIR})
        set(LIBRARY_OUTPUT_DIRECTORY ${SPARK_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_INSTALL_LIBDIR})
        set(RUNTIME_OUTPUT_DIRECTORY ${SPARK_OUTPUT_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_INSTALL_BINDIR})

        # Setup build output directories
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY} PARENT_SCOPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY} PARENT_SCOPE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY} PARENT_SCOPE)

        # Setup also per-config build output directories to simplify generator expression writing when needed.
        string(TOUPPER ${CMAKE_BUILD_TYPE} TYPE_UPPER)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${TYPE_UPPER} ${ARCHIVE_OUTPUT_DIRECTORY} PARENT_SCOPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${TYPE_UPPER} ${LIBRARY_OUTPUT_DIRECTORY} PARENT_SCOPE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${TYPE_UPPER} ${RUNTIME_OUTPUT_DIRECTORY} PARENT_SCOPE)
    endif()
endblock()

# Include our internal API for target definition
include(SPARKTarget)

# Set a default property for all targets so they are built by ALL
define_property(DIRECTORY PROPERTY DIR_IN_ALL INHERITED)
set_directory_properties(PROPERTIES DIR_IN_ALL ON)

set(CORE_NAME core)
set(CLIENT_NAME client)
set(SERVER_NAME server)

add_subdirectory(${CORE_NAME})
add_subdirectory(${CLIENT_NAME})
add_subdirectory(vendor)

if(NOT LINUX)
    add_subdirectory(${SERVER_NAME})
endif()
