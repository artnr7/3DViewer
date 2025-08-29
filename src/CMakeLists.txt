cmake_minimum_required(VERSION 4.0)

project(
  3DViewer
  VERSION 1.0.0
  LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# glob_vars
include(cmake/utils/glob_vars.cmake)


# find_packages
include(cmake/find_packages/qt.cmake)

# ############################# COVERAGE
include(cmake/targets/utils/gcov/Coverage.cmake)

# ############################# FORMAT
include(cmake/targets/utils/formatting/CMakeFormat.cmake)
include(cmake/targets/utils/formatting/ClangFormat.cmake)

# ############################# f
include(cmake/targets/utils/formatting/f.cmake)
