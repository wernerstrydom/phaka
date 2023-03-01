# Licensed to Werner Strydom under one or more agreements.
# Werner Strydom licenses this file to you under the MIT license.

set(CMAKE_C_VISIBILITY_PRESET       hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

configure_file(private-version.h.in private-version.h)

add_library(sdk SHARED phaka.c phaka.h)

include(GenerateExportHeader)
generate_export_header(sdk BASE_NAME PHAKA EXPORT_FILE_NAME phaka_export.h EXPORT_MACRO_NAME PHAKA_API)

target_include_directories(sdk PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(sdk INTERFACE .)

set_target_properties(sdk PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
set_target_properties(sdk PROPERTIES OUTPUT_NAME "phaka")
set_target_properties(sdk PROPERTIES PREFIX "")

install(TARGETS sdk
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT   Phaka_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   Phaka_Runtime
            NAMELINK_COMPONENT Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   Phaka_Development
        )


install(TARGETS sdk DESTINATION lib)
install(FILES phaka.h DESTINATION include/phaka)



