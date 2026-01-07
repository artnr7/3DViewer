cmake_minimum_required(VERSION 4.1.1)
project(
  3DViewer
  VERSION 1.0.0
  LANGUAGES CXX)

# global variables
include(cmake/utils/GlobalVariables.cmake)

# find packages
include(cmake/utils/FindPackages.cmake)

# assets management
include(cmake/utils/AssetsManagement.cmake)

# linker to qt and gtest
include(cmake/utils/TargetLinkFunctions.cmake)

# clang-format and cmake-format
include(cmake/formatting/ClangFormat.cmake)
include(cmake/formatting/CMakeFormat.cmake)
register_format_cmake_file()

# coverage
include(cmake/coverage/Coverage.cmake)

# build executable file
add_subdirectory(app)

# build tests add_subdirectory(tests)

# add targets for clang-format, cmake-format and coverage
create_clang_format_target()
create_cmake_format_target()
create_coverage_target()
