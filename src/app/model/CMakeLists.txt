set(MODEL_FILES
  model.cc
  model.h

  object_class/centetring_and_normalization.cc
  object_class/init.cc
  object_class/parse_f_lines.cc
  object_class/parser.cc
  object_class/parser_condition.cc
  object_class/parse_v_lines.cc
  object_class/utils.cc
  object_class/object_class.h
  object_class/types.h
)
register_format_sources(${MODEL_FILES})


add_library(model_lib STATIC ${MODEL_FILES})

target_include_directories(model_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(model_lib PRIVATE
  utils_lib
)

add_coverage_version(model_lib)
