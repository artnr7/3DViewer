register_format_cmake_file()

set(OBJECT_VIEWER_WIDGET_FILES
    gl.cc
    connections.cc
    init.cc
    object_viewer_widget.cc
    shaders.cc
    slots.cc
    events.cc
    object_viewer_widget.h)
register_format_sources(${OBJECT_VIEWER_WIDGET_FILES})

add_library(object_viewer_widget_lib STATIC ${OBJECT_VIEWER_WIDGET_FILES})

target_include_directories(object_viewer_widget_lib
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_qt(object_viewer_widget_lib)
