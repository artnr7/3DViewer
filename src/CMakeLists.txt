cmake_minimum_required(VERSION 4.1.1)
project(3dviewer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# glob_vars
include(cmake/utils/GlobVars.cmake)

# find_packages
include(cmake/FindPackages.cmake)

# clang-format
include(cmake/targets/utils/formatting/FormatHelper.cmake)

# linker to qt
include(cmake/QtInterface.cmake)

add_subdirectory(app)

# add fix and check clang-format targets
create_format_target()
