function(add_assets_folder TARGET_NAME)
  add_custom_command(
    TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets
            ${CMAKE_BINARY_DIR}/assets)
endfunction()
