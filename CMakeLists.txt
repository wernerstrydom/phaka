# Licensed to Werner Strydom under one or more agreements.
# Werner Strydom licenses this file to you under the MIT license.
# See the LICENSE file in the project root for more information.

cmake_minimum_required(VERSION 3.24)

IF (DEFINED ENV{PHAKA_VERSION})
    set(PHAKA_VERSION $ENV{PHAKA_VERSION})
ELSE ()
    IF (DEFINED ENV{BUILD_NUMBER})
        set(PHAKA_BUILD_NUMBER $ENV{BUILD_NUMBER})
    ELSE ()
        set(PHAKA_BUILD_NUMBER 1)
    ENDIF ()
    set(PHAKA_VERSION "0.1.${PHAKA_BUILD_NUMBER}.0")
ENDIF ()

project(Phaka
        HOMEPAGE_URL "https://wernerstrydom.com"
        DESCRIPTION "A tool to assist with release engineering"
        VERSION "${PHAKA_VERSION}"
        LANGUAGES C)

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

# don't set the install prefix if it was already set
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "CMAKE_INSTALL_PREFIX was set to ${CMAKE_INSTALL_PREFIX}")
    if (WINDOWS)
        message(STATUS "Setting install prefix to according to Windows conventions")
        if (CMAKE_SIZEOF_VOID_P MATCHES "8")
            set(CMAKE_INSTALL_PREFIX "C:/Program Files/${CMAKE_PROJECT_NAME}" CACHE PATH "default install path" FORCE)
        else ()
            set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/${CMAKE_PROJECT_NAME}" CACHE PATH "default install path" FORCE)
        endif ()
    elseif (APPLE)
        message(STATUS "Setting install prefix to according to Apple conventions")
        set(CMAKE_INSTALL_PREFIX "/Library/${CMAKE_PROJECT_NAME}" CACHE PATH "default install path" FORCE)
    elseif (UNIX)
        message(STATUS "Setting install prefix to according to UNIX conventions")
        string(TOLOWER "${CMAKE_PROJECT_NAME}" CMAKE_PROJECT_NAME_LOWER)
        set(CMAKE_INSTALL_PREFIX "/opt/${CMAKE_PROJECT_NAME_LOWER}" CACHE PATH "default install path" FORCE)
    endif ()
endif ()
message(STATUS "CMAKE_INSTALL_PREFIX*: ${CMAKE_INSTALL_PREFIX}")


add_subdirectory(src)

include(InstallRequiredSystemLibraries)

message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")

find_program(PHAKA_EXECUTABLE phaka
        HINTS ${CMAKE_SOURCE_DIR}/bin ${CMAKE_BINARY_DIR}/bin /usr/local/bin /usr/bin /bin /opt/bin /opt/local/bin /opt/phaka/bin /Library/Phaka/bin
        NO_DEFAULT_PATH)

if (PHAKA_EXECUTABLE)
    message(STATUS "Found phaka: ${PHAKA_EXECUTABLE}")
    execute_process(COMMAND ${PHAKA_EXECUTABLE} arch
            OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(COMMAND ${PHAKA_EXECUTABLE} system
            OUTPUT_VARIABLE CPACK_SYSTEM_NAME
            OUTPUT_STRIP_TRAILING_WHITESPACE)
else ()
    # this allows us to bootstrap the build process
    set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
    set(CPACK_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
endif ()

message(STATUS "CPACK_SYSTEM_NAME: ${CPACK_SYSTEM_NAME}")
message(STATUS "CPACK_PACKAGE_ARCHITECTURE: ${CPACK_PACKAGE_ARCHITECTURE}")

if (CPACK_SYSTEM_NAME STREQUAL "linux")
    set(CPACK_GENERATOR "ZIP;TGZ")
elseif (CPACK_SYSTEM_NAME STREQUAL "darwin")
    set(CPACK_GENERATOR "ZIP;TGZ")
elseif (CPACK_SYSTEM_NAME STREQUAL "windows")
    set(CPACK_GENERATOR "ZIP")
else ()
    set(CPACK_GENERATOR "ZIP")
endif ()

message(STATUS "CPACK_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
set(CPACK_STRIP_FILES YES)
set(CPACK_PACKAGE_VENDOR "Werner Strydom")
set(CPACK_PACKAGE_CONTACT "hello@phaka.org")
string(TOLOWER "${CMAKE_PROJECT_NAME}" CPACK_PACKAGE_NAME)
string(TOLOWER "${CMAKE_SYSTEM_NAME}" CPACK_SYSTEM_NAME)
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CMAKE_PROJECT_DESCRIPTION}")

# Sets the output paths so we can upload the packages to GitHub
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/artifacts")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
if (CPACK_PACKAGE_ARCHITECTURE)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-${CPACK_PACKAGE_ARCHITECTURE}")
endif ()
include(CPack)
