register_format_cmake_file()

# set (PARSER_LIB_NAME parser_lib)

set(PARSER_FILES
    centetring_and_normalization.cc
    init.cc
    parse_f_lines.cc
    parser.cc
    parser_condition.cc
    parse_v_lines.cc
    utils.cc
    object_class.h
    types.h
)

register_format_sources(${PARSER_FILES})

add_library(parser_lib STATIC ${PARSER_FILES})

target_include_directories(parser_lib  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_coverage_version(parser_lib)
