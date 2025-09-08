include(cmake/srcs/Parser.cmake)

set(TEST_PARSER test_parser)
set(TEST_PARSER_FILES ${TEST_PARSER}_files)
set(RUN_TEST_PARSER run_${TEST_PARSER})

set(TEST_PARSER_FILES ${PARSER_SRC} ${PARSER_INCLUDE})

add_executable(${TEST_PARSER} ${TEST_PARSER_FILES})

set_target_properties(
  ${TEST_PARSER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                            "${CMAKE_SOURCE_DIR}/${INSTALL_DIR}")

target_compile_options(${TEST_PARSER} PRIVATE -Wall -Werror -Wextra)

target_link_libraries(${TEST_PARSER} PRIVATE Qt6::OpenGL)

add_custom_target(
  ${RUN_TEST_PARSER}
  COMMAND "${CMAKE_SOURCE_DIR}/${INSTALL_DIR}/${TEST_PARSER}"
  DEPENDS ${TEST_PARSER})
