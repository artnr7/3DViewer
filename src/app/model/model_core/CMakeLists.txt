register_format_cmake_file()

#* model_core_types interface *#
set(MODEL_CORE_TYPES_FILES
  interface/model_core_types.h
)
register_format_sources(${MODEL_CORE_TYPES_FILES})

add_library(model_core_types INTERFACE)
target_include_directories(model_core_types INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
## model_core_types interface

#* model_core library *#
set(MODEL_CORE_FILES
  model_core.cc
  model_core.h
)
register_format_sources(${MODEL_CORE_FILES})

add_library(model_core_lib STATIC ${MODEL_CORE_FILES})
target_include_directories(model_core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(model_core_lib PUBLIC model_core_types)

add_coverage_version(model_core_lib)
## model_core library
