cmake_minimum_required(VERSION 4.1.1)
project(3DViewer VERSION 1.0.0 LANGUAGES CXX)

# Global variables
include(cmake/utils/GlobVars.cmake)

# find_packages
include(cmake/FindPackages.cmake)

# clang-format
include(cmake/targets/utils/formatting/FormatHelper.cmake)

# linker to qt and gtest
include(cmake/TargetLinkFunctions.cmake)

# coverage
include(cmake/Coverage.cmake)

# build executable file
add_subdirectory(app)

# build tests
add_subdirectory(tests)

# add targets for clang-format and coverage
create_format_target()
create_coverage_target()

# # GDB
# include(cmake/targets/GDB.cmake)

# # ############################# FORMAT
# include(cmake/targets/utils/formatting/CMakeFormat.cmake)
