set(AFFINE_TEST_FILES
  affine_transformations.cc
)

add_executable(test_affine_transformations
  ${AFFINE_TEST_FILES}
)

target_link_libraries_with_coverage(test_affine_transformations model_lib)
target_link_gtest(test_affine_transformations)
register_coverage_tests(test_affine_transformations)

add_test(NAME affine_transformations
  COMMAND test_affine_transformations
)
