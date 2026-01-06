function(add_qt_interface TARGET_NAME)
  target_link_libraries(${TARGET_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::OpenGL
    Qt6::Gui
  )
endfunction()