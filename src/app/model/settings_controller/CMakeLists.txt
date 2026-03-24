register_format_cmake_file()

# set (PARSER_LIB_NAME parser_lib)

set(SETTINGS_PARSER_FILES settings_controller.h)

register_format_sources(${SETTINGS_PARSER_FILES})

add_library(settings_parser_lib STATIC ${SETTINGS_PARSER_FILES})

add_coverage_version(settings_parser_lib)
