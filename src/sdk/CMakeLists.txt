# Licensed to Werner Strydom under one or more agreements.
# Werner Strydom licenses this file to you under the MIT license.

set(CMAKE_C_VISIBILITY_PRESET       hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

configure_file(private-version.h.in private-version.h)

add_library(sdk SHARED phaka.c phaka.h private-platform.h)

include(GenerateExportHeader)
generate_export_header(sdk BASE_NAME PHAKA EXPORT_FILE_NAME phaka_export.h EXPORT_MACRO_NAME PHAKA_API)

target_include_directories(sdk PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(sdk INTERFACE .)

set_target_properties(sdk PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
set_target_properties(sdk PROPERTIES OUTPUT_NAME "phaka")
set_target_properties(sdk PROPERTIES PREFIX "")

find_package( Doxygen )
if ( DOXYGEN_FOUND )
    message( "Found Doxygen" )
    set( DOXYGEN_OUTPUT_DIRECTORY docs )
    set(DOXYGEN_PROJECT_NAME "Phaka")
    set(DOXYGEN_PROJECT_BRIEF "A tool to assist with release engineering")
    set(DOXYGEN_PROJECT_NUMBER "${PHAKA_VERSION}")
    set(DOXYGEN_EXCLUDE_PATTERNS "private-*.h")
    set(DOXYGEN_FILE_PATTERNS "*.h")

    set(OPTIMIZE_OUTPUT_FOR_C YES)
    # only generate docs for the public API
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_EXTRACT_PRIVATE NO)
    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_EXTRACT_LOCALCLASSES NO)
    set(DOXYGEN_EXTRACT_LOCALDEFINES NO)
    set(DOXYGEN_EXTRACT_LOCALENUMS NO)
    set(DOXYGEN_EXTRACT_LOCALINTERFACES NO)
    set(DOXYGEN_EXTRACT_LOCALMACROS NO)
    set(DOXYGEN_EXTRACT_LOCALMETHODS NO)
    set(DOXYGEN_EXTRACT_LOCALTYPEDEFS NO)
    set(DOXYGEN_EXTRACT_LOCALUNIONS NO)
    set(DOXYGEN_EXTRACT_LOCALVARIABLES NO)
    set(DOXYGEN_GENERATE_TODOLIST YES)
    set(DOXYGEN_GENERATE_TESTLIST YES)
    set(DOXYGEN_GENERATE_BUGLIST YES)
    set(DOXYGEN_GENERATE_DEPRECATEDLIST YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_GENERATE_HTMLHELP NO)
    set(DOXYGEN_GENERATE_QHP NO)
    set(DOXYGEN_GENERATE_DOCSET NO)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_GENERATE_RTF NO)
    set(DOXYGEN_GENERATE_XML YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_SHOW_NAMESPACES NO)
    set(DOXYGEN_XML_PROGRAMLISTING NO)

    doxygen_add_docs(sdkdocs ${CMAKE_CURRENT_SOURCE_DIR}   )
else()
    message( "Doxygen need to be installed to generate the doxygen documentation" )
endif()

install(TARGETS sdk
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT   Phaka_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   Phaka_Runtime
            NAMELINK_COMPONENT Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   Phaka_Development
        )

install(FILES phaka.h DESTINATION include/phaka)


find_package( Doxygen )





