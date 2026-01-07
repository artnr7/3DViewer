include_guard()

function(target_link_gtest TARGET_NAME)
  target_link_libraries(${TARGET_NAME} PRIVATE GTest::gtest GTest::gtest_main
                                               Threads::Threads)
endfunction()

function(target_link_qt TARGET_NAME)
  target_link_libraries(
    ${TARGET_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets
                           Qt6::OpenGL Qt6::Gui)
endfunction()
