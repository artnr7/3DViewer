add_library(controller_lib STATIC
  controller.cc
  controller.h
)

target_include_directories(controller_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(controller_lib PRIVATE
  model_lib
  view_lib
)
