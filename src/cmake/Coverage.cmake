function(add_coverage_version LIB_NAME)
  if(NOT ENABLE_COVERAGE)
    return()
  endif()

  set(COV_LIB_NAME ${LIB_NAME}_coverage)
  get_target_property(SOURCES ${LIB_NAME} SOURCES)
  add_library(${COV_LIB_NAME} STATIC ${SOURCES})

  get_target_property(ALL_INCS ${LIB_NAME} INCLUDE_DIRECTORIES)
  if(ALL_INCS)
    target_include_directories(${COV_LIB_NAME} PUBLIC ${ALL_INCS})
  endif()

  get_target_property(INTERFACE_INCS ${LIB_NAME} INTERFACE_INCLUDE_DIRECTORIES)
  if(INTERFACE_INCS)
    target_include_directories(${COV_LIB_NAME} PUBLIC ${INTERFACE_INCS})
  endif()

  get_target_property(LINK_LIBS ${LIB_NAME} LINK_LIBRARIES)
  if(LINK_LIBS)
    target_link_libraries(${COV_LIB_NAME} PUBLIC ${LINK_LIBS})
  endif()

  get_target_property(INTERFACE_LIBS ${LIB_NAME} INTERFACE_LINK_LIBRARIES)
  if(INTERFACE_LIBS)
    target_link_libraries(${COV_LIB_NAME} PUBLIC ${INTERFACE_LIBS})
  endif()

  target_compile_options(${COV_LIB_NAME} PRIVATE --coverage -g -O0)
  target_link_options(${COV_LIB_NAME} PRIVATE --coverage)

  get_target_property(COMPILE_DEFS ${LIB_NAME} COMPILE_DEFINITIONS)
  if(COMPILE_DEFS)
    target_compile_definitions(${COV_LIB_NAME} PUBLIC ${COMPILE_DEFS})
  endif()
endfunction()

function(target_add_coverage TARGET_NAME)
  if(ENABLE_COVERAGE)
    target_compile_options(${TARGET_NAME} PRIVATE --coverage -g -O0)
    target_link_options(${TARGET_NAME}  PRIVATE --coverage)
  endif()
endfunction()

function(target_link_libraries_with_coverage TEST_TARGET)
  foreach(LIB ${ARGN})
    if(ENABLE_COVERAGE AND TARGET ${LIB}_coverage)
      target_link_libraries(${TEST_TARGET} PRIVATE ${LIB}_coverage)
    else()
      target_link_libraries(${TEST_TARGET} PRIVATE ${LIB})
    endif()
  endforeach()
endfunction()

set(COVERAGE_TESTS "" CACHE INTERNAL "Test targets for coverage")

macro(register_coverage_tests)
  foreach(TEST ${ARGN})
    list(APPEND COVERAGE_TESTS ${TEST})
    target_add_coverage(${TEST})
  endforeach()
  set(COVERAGE_TESTS ${COVERAGE_TESTS} CACHE INTERNAL "")
endmacro()

function(create_coverage_target)
  if(NOT ENABLE_COVERAGE)
    message(STATUS "Coverage disabled, skipping target creation")
    return()
  endif()

  string(REPLACE ";" " " TESTS_FOR_BASH "${COVERAGE_TESTS}")

  add_custom_target(coverage
    COMMAND echo "=== Cleaning old coverage data ==="
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete 2>/dev/null || true

    COMMAND echo "=== Rebuilding tests ==="
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${COVERAGE_TESTS}

    COMMAND echo "=== Running tests ==="
    COMMAND bash -c "for test in ${TESTS_FOR_BASH}; do echo \"--- Running \$test ---\"; ${CMAKE_BINARY_DIR}/bin/\$test > /dev/null 2>&1 || true; done"

    COMMAND echo "=== Collecting coverage ==="
    COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info --ignore-errors mismatch,inconsistent

    COMMAND echo "=== Filtering coverage ==="
    COMMAND ${LCOV} --remove ${CMAKE_BINARY_DIR}/coverage.info /usr/* */gtest/* --output-file ${CMAKE_BINARY_DIR}/coverage_filtered.info --ignore-errors inconsistent,unused

    COMMAND echo "=== Generating HTML report ==="
    COMMAND ${GENHTML} --output-directory ${CMAKE_BINARY_DIR}/coverage ${CMAKE_BINARY_DIR}/coverage_filtered.info

    COMMAND echo ""
    COMMAND echo "========================================"
    COMMAND echo "COVERAGE REPORT GENERATED"
    COMMAND echo "========================================"
    COMMAND echo "Open: file://${CMAKE_BINARY_DIR}/coverage/index.html"
    COMMAND echo "Tests run: ${TESTS_FOR_BASH}"
    COMMAND echo "========================================"
    COMMAND ${LCOV} --summary ${CMAKE_BINARY_DIR}/coverage_filtered.info 2>/dev/null | grep -E "lines|functions" || echo "No coverage data"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generate code coverage report"
    COMMAND echo "========================================"
    VERBATIM
  )

  add_custom_target(coverage-clean
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcno" -delete
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/coverage
    COMMAND rm -f ${CMAKE_BINARY_DIR}/coverage*.info
    COMMENT "Clean coverage data"
    VERBATIM
  )

  message(STATUS "Target 'coverage' created")
endfunction()