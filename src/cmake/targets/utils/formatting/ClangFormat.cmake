find_program(CLANG_FORMAT clang-format)

file(GLOB_RECURSE CLANG_FILES "app/*.c" "app/*.h" "app/*.cc" "app/*.hpp")
# string(REPLACE ";" " " CLANG_FILES_SRC "${CLANG_FILES}") "*.h"  "*.c" "*.hpp"
# "*.cc" set(CLANG_FILES_WW ${CLANG_FILES_SRC}) set(CLANG_FILES_WW
# /home/atrnr7/3DViewer/src/app/view/src/app.cc)

# set(CLANG_FILES_SRC ${CLANG_FILES_W}) message(${CLANG_FILES_SRC})
# message(${CLANG_FORMAT}   --style=Google   -i   "${CLANG_FILES_WW}")
# message("CLANG_FILES: ${CLANG_FILES}") message("CLANG_FILES_WW:
# ${CLANG_FILES_WW}")

# foreach(file IN LISTS CLANG_FILES) message("file: ${file}") endforeach()

add_custom_target(
  clang_format_fix
  COMMAND ${CLANG_FORMAT} --style=Google -i ${CLANG_FILES}
  COMMENT "${CLANG_FORMAT} done"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
