register_format_cmake_file()

# set (PARSER_LIB_NAME parser_lib)

set(PARSER_FILES
    parser/parser.cc
    parser/parse_f_lines.cc
    parser/parse_v_lines.cc
    parser/parser_condition.cc
    affine/affine.cc
    utils.cc
    alignment.cc
    object.h
    types.h)

register_format_sources(${PARSER_FILES})

add_library(parser_lib STATIC ${PARSER_FILES})

target_include_directories(parser_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_coverage_version(parser_lib)
