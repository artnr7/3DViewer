register_format_cmake_file()

#* controller library *#
set(CONTROLLER_FILES controller.cc controller.h)
register_format_sources(${CONTROLLER_FILES})

add_library(controller_lib STATIC ${CONTROLLER_FILES})

target_include_directories(controller_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(controller_lib PUBLIC model_lib model_types action_types enum_utils_lib)

target_link_qt(controller_lib)
## controller library
