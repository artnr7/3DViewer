set(SNAKE_COVERAGE_TEST snake_coverage_test)

add_executable(${SNAKE_COVERAGE_TEST} ${SNAKE_TEST_FILES}
                                      ${SNAKE_BACK_SRC_INCLUDE})

target_link_libraries(
  ${SNAKE_COVERAGE_TEST} PRIVATE GTest::GTest GTest::Main Threads::Threads
                                 snake_back_lib_dsnake)

target_compile_options(
  ${SNAKE_COVERAGE_TEST}
  PRIVATE -Wall
          -Wextra
          -Werror
          --coverage
          -lgtest
          -lgtest_main
          -lpthread)

target_link_options(${SNAKE_COVERAGE_TEST} PRIVATE --coverage)

target_include_directories(${SNAKE_COVERAGE_TEST} PRIVATE ${CMAKE_SOURCE_DIR})

add_custom_target(
  run_coverage_${SNAKE_COVERAGE_TEST}
  COMMAND ./${SNAKE_COVERAGE_TEST}
  DEPENDS ${SNAKE_COVERAGE_TEST}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# Глобальная цель coverage find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

set(COVERAGE_DIR "${CMAKE_SOURCE_DIR}/coverage")

# if(LCOV_PATH AND GENHTML_PATH)
add_custom_target(
  coverage_all
  COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target
          ${SNAKE_COVERAGE_TEST}
  COMMAND ${CMAKE_BINARY_DIR}/${SNAKE_COVERAGE_TEST} # Запускаем тесты для
                                                     # генерации покрытий
  COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR} --output-file
          coverage.info -ignore-errors mismatch
  COMMAND lcov --remove coverage.info '/usr/include/*' --output-file
          coverage_filtered.info
  COMMAND genhtml --output-directory ${COVERAGE_DIR} coverage_filtered.info
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DEPENDS ${SNAKE_COVERAGE_TEST})
# else() message(WARNING "lcov or genhtml not found - coverage targets
# disabled") endif()
