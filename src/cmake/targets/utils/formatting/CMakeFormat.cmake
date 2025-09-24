find_program(CMAKE_FORMAT cmake-format)

file(GLOB_RECURSE CMAKE_FILES "cmake/*.cmake" "CMakeLists.txt")
# string(REPLACE ";" " " CMAKE_FILES_SRC "${CMAKE_FILES}")

add_custom_target(
  cmake_format_fix
  COMMAND ${CMAKE_FORMAT} -i ${CMAKE_FILES}
  COMMENT "${CMAKE_FORMAT} done")
