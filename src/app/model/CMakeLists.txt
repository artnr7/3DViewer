# set(MODEL_LIB_NAME model_lib)
register_format_cmake_file()

add_subdirectory(object)
add_subdirectory(settings_controller)

# * model library *
set(MODEL_FILES model.h getters.cc setters.cc)
register_format_sources(${MODEL_FILES})

add_library(model_lib STATIC ${MODEL_FILES})

target_include_directories(model_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(model_lib PUBLIC parser_lib)
target_link_qt(model_lib)

add_coverage_version(model_lib)
# model library
