set(MODEL_LIB_NAME model_lib)
register_format_cmake_file()

add_subdirectory(object_class)

#* model library *#
set(MODEL_FILES
    model.cc
    model.h
)
register_format_sources(${MODEL_FILES})

add_library(${MODEL_LIB_NAME} STATIC ${MODEL_FILES})

target_include_directories(${MODEL_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${MODEL_LIB_NAME} PRIVATE ${PARSER_LIB_NAME})
target_link_qt(${MODEL_LIB_NAME})

add_coverage_version(${MODEL_LIB_NAME})
## model library
