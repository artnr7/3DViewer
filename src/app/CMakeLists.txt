add_executable(${PROJECT_NAME} 3dviewer.cc)

add_subdirectory(controller)
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(utils)

target_link_libraries(${PROJECT_NAME} PRIVATE controller_lib model_lib view_lib
                                              utils_lib)

target_link_qt(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

register_format_cmake_file()
