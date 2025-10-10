add_custom_target(
  run_gdb
  # COMMAND
  #   /root/.local/share/pipx/venvs/gdbgui/bin/gdbgui -g
  #   "gdb -x /home/atrnr7/3DViewer/src/.gdbinit  ${INSTALL_DIR}/${3DVIEWER_APP}" 
  COMMAND gdb -tui -x ../configs/.gdbinit "${INSTALL_DIR}/${3DVIEWER_APP}"
  DEPENDS ${3DVIEWER_APP})
