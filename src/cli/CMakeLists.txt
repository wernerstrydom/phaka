# Licensed to Werner Strydom under one or more agreements.
# Werner Strydom licenses this file to you under the MIT license.
# See the LICENSE file in the project root for more information.
set(CMAKE_C_STANDARD 99)
message(STATUS "CMAKE_INSTALL_BINDIR: ${CMAKE_INSTALL_BINDIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR: ${CMAKE_INSTALL_LIBDIR}")

file(RELATIVE_PATH relativeRpath
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        )

add_executable(cli main.c)

if(APPLE)
    set_target_properties(cli PROPERTIES INSTALL_RPATH "@loader_path;@loader_path/${relativeRpath}")
elseif(UNIX)
    set_target_properties(cli PROPERTIES INSTALL_RPATH "$ORIGIN:$ORIGIN/${relativeRpath}")
    set_target_properties(cli PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

set_target_properties(cli PROPERTIES OUTPUT_NAME "phaka")
target_link_libraries(cli PUBLIC sdk)

install(TARGETS cli
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT   Phaka_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   Phaka_Runtime
            NAMELINK_COMPONENT Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   Phaka_Development
        )
