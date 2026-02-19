register_format_cmake_file()

add_subdirectory(model_core)

#* model_types interface *#
set(MODEL_TYPES_FILES
  interface/model_types.h
)
register_format_sources(${MODEL_TYPES_FILES})

add_library(model_types INTERFACE)
target_include_directories(model_types INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
target_link_libraries(model_types INTERFACE model_core_types)
## model_types interface

#* model library *#
set(MODEL_FILES
    model.cc
    model.h
    # object_class/centetring_and_normalization.cc
    # object_class/init.cc
    # object_class/parse_f_lines.cc
    # object_class/parser.cc
    # object_class/parser_condition.cc
    # object_class/parse_v_lines.cc
    # object_class/utils.cc
    # object_class/object_class.h
    # object_class/types.h
)
register_format_sources(${MODEL_FILES})

add_library(model_lib STATIC ${MODEL_FILES})

target_include_directories(model_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(model_lib PUBLIC model_core_lib PRIVATE model_types)
target_link_qt(model_lib)

add_coverage_version(model_lib)
## model library
