cmake_minimum_required(VERSION 3.6)

project(libelfinexamples)
add_subdirectory(../rapidjson rapidjsondir)

add_executable(dump-lines dump-lines.cc)
target_link_libraries(dump-lines dwarf)

add_executable(dump-sections dump-sections.cc)
target_link_libraries(dump-sections dwarf)

add_executable(dump-segments dump-segments.cc)
target_link_libraries(dump-segments dwarf)

add_executable(dump-syms dump-syms.cc)
target_link_libraries(dump-syms dwarf)

add_executable(dump-tree dump-tree.cc)
target_link_libraries(dump-tree dwarf)

add_executable(dump-json dump-json.cc)
target_link_libraries(dump-json dwarf)
target_compile_definitions(dump-json PUBLIC RAPIDJSON_HAS_STDSTRING=1)
target_include_directories(dump-json PUBLIC ../rapidjson/include)
add_dependencies(dump-json smallsample)

add_executable(find-pc find-pc.cc)
target_link_libraries(find-pc dwarf)

add_executable(smallsample smallsample.cc)
