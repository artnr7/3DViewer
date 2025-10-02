#include "../../../utils/logger.hpp"
#include "menu_widget.hpp"

void s21::MenuWidget::CreateNewObjectImitated() {
  static int i = 0;
  if (i++) return;

  // const std::string &obj_filename = "../objs/cube.obj";
  // const std::string &obj_filename = "../objs/2.obj";
  const std::string &obj_filename = "../objs/FinalBaseMesh.obj";
  s21::Logger::Log()->Msg("Введено имя файла " + obj_filename);
  emit NewFilenameEntered(obj_filename);
}