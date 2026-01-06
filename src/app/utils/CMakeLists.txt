set(UTILS_FILES
  exception.h
  logger.h
)

add_library(utils_lib INTERFACE ${UTILS_FILES})
register_format_sources(${UTILS_FILES})

target_include_directories(utils_lib INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
