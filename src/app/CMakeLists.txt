register_format_cmake_file()

set(MAIN_FILES 3dviewer.cc)
register_format_sources(${MAIN_FILES})

add_executable(${PROJECT_NAME} ${MAIN_FILES})

add_subdirectory(utils)
add_subdirectory(model)
add_subdirectory(controller)
add_subdirectory(view)

target_link_libraries(${PROJECT_NAME} PRIVATE view_lib controller_lib model_lib utils_lib)

target_link_qt(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_assets_folder(${PROJECT_NAME})
