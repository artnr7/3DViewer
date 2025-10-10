cmake_minimum_required(VERSION 4.1.1)

project(
  3DViewer
  VERSION 1.0.0
  LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

# glob_vars
include(cmake/utils/glob_vars.cmake)

# find_packages
include(cmake/find_packages/qt.cmake)

# 3DViewer
include(cmake/targets/main/AppExe.cmake)

# GDB
include(cmake/targets/GDB.cmake)

# test parser include(cmake/targets/test_parser/Parser.cmake)

# ############################# COVERAGE
# include(cmake/targets/utils/gcov/Coverage.cmake)

# ############################# FORMAT
include(cmake/targets/utils/formatting/CMakeFormat.cmake)
include(cmake/targets/utils/formatting/ClangFormat.cmake)
