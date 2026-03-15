#include "obj_v_wid.h"
#include <QRadioButton>
#include <qcoreevent.h>
#include <qevent.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qtimer.h>

#include "../../utils/logger.h"
namespace s21 {

void ObjectViewerWidget::OnFrontUpdateTimer() {
  // Lg::Log()->Info(std::string(__func__));
  update();

  emit BackgroundColorUpdate();

  if (file_uploaded_) {
    emit ActionGetGLVertices();
    emit EdgeColorUpdate();
    emit LineWidthUpdate();
    emit VerticesSizeUpdate();
    emit VerticeStyleUpdate();
    emit ContinuityLineUpdate();
    emit VertexClrUpd();
  }
}

} // namespace s21
