register_format_cmake_file()

set(PARSER_TEST_FILES parser.cc)

add_executable(test_parser ${PARSER_TEST_FILES})

target_link_libraries_with_coverage(test_parser model_lib)
target_link_gtest(test_parser)
register_format_sources(${PARSER_TEST_FILES})
register_coverage_tests(test_parser)

add_test(NAME parser COMMAND test_parser)
