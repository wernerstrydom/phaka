set(CMAKE_C_STANDARD 99)

add_executable(cli main.c)

set_target_properties(cli PROPERTIES OUTPUT_NAME "phaka")

install(TARGETS cli DESTINATION bin)
