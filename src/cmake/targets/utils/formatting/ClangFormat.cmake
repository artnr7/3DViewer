file(GLOB_RECURSE CLANG_FILES "*.c" "*.h" "*.cc" "*.hpp")

add_custom_target(
  clang_f
  COMMAND clang-format -i ${CLANG_FILES}
  COMMENT "Clang-format done"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
