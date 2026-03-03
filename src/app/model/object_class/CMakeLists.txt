register_format_cmake_file()

# set (PARSER_LIB_NAME parser_lib)

set(PARSER_FILES
    parser_src/parser.cc
    parser_src/parse_f_lines.cc
    parser_src/parse_v_lines.cc
    parser_src/parser_condition.cc

    affine_src/affine.cc

    init.cc
    utils.cc
    alignment.cc
    object_class.h
    types.h
)

register_format_sources(${PARSER_FILES})

add_library(parser_lib STATIC ${PARSER_FILES})

target_include_directories(parser_lib  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_coverage_version(parser_lib)
