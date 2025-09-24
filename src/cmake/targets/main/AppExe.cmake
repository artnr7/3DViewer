include(cmake/srcs/View.cmake)
include(cmake/srcs/Controller.cmake)
include(cmake/srcs/Model.cmake)
include(cmake/srcs/MainFile.cmake)

set(3DVIEWER_APP 3dviewer)
set(RUN_3DVIEWER run_${3DVIEWER_APP})

set(3DVIEWER_SRC
    ${MAIN_FILE} ${VIEW_SRC} ${VIEW_INCLUDE}
    # ${CONTROLLER_SRC} ${CONTROLLER_INCLUDE} ${MODEL_SRC} ${MODEL_INCLUDE}
)

add_executable(${3DVIEWER_APP} ${3DVIEWER_SRC})

set_target_properties(${3DVIEWER_APP} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                 "${INSTALL_DIR}")

target_compile_options(${3DVIEWER_APP} PRIVATE -Wall -Werror -Wextra)

target_link_libraries(
  ${3DVIEWER_APP} PRIVATE Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets Qt6::OpenGL
                          Qt6::Gui)

add_custom_target(
  ${RUN_3DVIEWER}
  COMMAND "${INSTALL_DIR}/${3DVIEWER_APP}"
  DEPENDS ${3DVIEWER_APP})
