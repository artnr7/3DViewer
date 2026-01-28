register_format_cmake_file()

set(CONTROLLER_FILES controller.cc controller.h)

add_library(controller_lib STATIC ${CONTROLLER_FILES})
register_format_sources(${CONTROLLER_FILES})

target_include_directories(controller_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(controller_lib PUBLIC model_lib common_types)

target_link_qt(controller_lib)
