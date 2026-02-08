register_format_cmake_file()

#* Enum utils library *#
set(ENUM_UTILS_FILES enum.h)
register_format_sources(${ENUM_UTILS_FILES})

add_library(enum_utils_lib INTERFACE ${ENUM_UTILS_FILES})
target_include_directories(enum_utils_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
## Enum utils library

set(UTILS_FILES exception.h logger.h)
register_format_sources(${UTILS_FILES})

add_library(utils_lib INTERFACE ${UTILS_FILES})
target_include_directories(utils_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
