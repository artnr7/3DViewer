#include <qlogging.h>

#include <string>

#include "action_types.h"
#include "config.h"
#include "enum.h"
#include "logger.h"
#include "view.h"

namespace s21 {

View::View(Controller* controller, QWidget* parent)
    : QWidget(parent), pcontroller_(controller) {
  Lg::Log()->Info(std::string(__func__) + " constuctor");
  setWindowTitle("3DViewer");
  setGeometry(INIT_AX_MAIN_WINDOW, INIT_AY_MAIN_WINDOW, INIT_W_MAIN_WINDOW,
              INIT_H_MAIN_WINDOW);

  pmenu_wid_ = new MenuWidget(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET, this);

  pobj_v_wid_ =
      new ObjectViewerWidget(INIT_AX_OBJECT_WIDGET, INIT_AY_OBJECT_WIDGET,
                             INIT_W_OBJECT_WIDGET, INIT_H_OBJECT_WIDGET, this);

  menu_wid_update_timer_ = new QTimer(this);

  SetupConnections();
  // TODO:(sundaeka) надо считать настройки до состояния когда можно уже
  // загружать файл
}
void View::OnObjectStartBuild() {
  // по сути это надо вызывать, когда есть уверенность, что файл в модели
  // загружен
  Lg::Log()->Info("View:" + std::string(__func__));

  // menu
  menu_wid_update_timer_->start(16);
  // obj_widget
  pobj_v_wid_->ObjectInit();
}

void View::SetupConnections() {
  Lg::Log()->Info("View::" + std::string(__func__));

  // menu_wid
  // эт когда меню данны в модель посылает
  // connect(pmenu_wid_, &MenuWidget::ActionTriggered, this,
  //         &View::OnActionTriggered);

  // // это когда уже запущенный таймер менюшки хочет данные обновить
  // connect(menu_wid_update_timer_, &QTimer::timeout, this,
  //         &View::OnMenuWidgetTimerUpdated);
  //

  // Affine
  connect(pobj_v_wid_, &ObjectViewerWidget::updGLVertRequested, this,
          &View::updGLVert);

  connect(pobj_v_wid_, &ObjectViewerWidget::MouseTransYChanged, this,
          &View::updTransY);
  connect(pobj_v_wid_, &ObjectViewerWidget::MouseTransXChanged, this,
          &View::updTransX);

  connect(pobj_v_wid_, &ObjectViewerWidget::MouseRotYChanged, this,
          &View::updRotY);
  connect(pobj_v_wid_, &ObjectViewerWidget::MouseRotXChanged, this,
          &View::updRotX);

  // Vert
  connect(pobj_v_wid_, &ObjectViewerWidget::updVertSzRequested, this,
          &View::updVertSz);

  connect(pobj_v_wid_, &ObjectViewerWidget::updVertStyleRequested, this,
          &View::updVertStyle);

  connect(pobj_v_wid_, &ObjectViewerWidget::updVertClrRequested, this,
          &View::updVertClr);

  // Edge
  connect(pobj_v_wid_, &ObjectViewerWidget::updEdgeSzRequested, this,
          &View::updEdgeSz);

  connect(pobj_v_wid_, &ObjectViewerWidget::updEdgeStyleRequested, this,
          &View::updEdgeStyle);

  connect(pobj_v_wid_, &ObjectViewerWidget::updEdgeClrRequested, this,
          &View::updEdgeClr);

  // Misc
  connect(pobj_v_wid_, &ObjectViewerWidget::updBckgClrRequested, this,
          &View::updBckgClr);
}

// void View::OnMouseUpdated() { OnActionTriggered(SceneAction::kRotateX, pos) }

void View::OnActionTriggered(SceneAction action, ActionData data) {
  Lg::Log()->Trace("View::" + std::string(__func__));

  // std::visit(
  //     [this, action](auto &&arg) {
  //       using T = std::decay_t<decltype(arg)>;
  //
  //       if constexpr (std::is_same_v<T, float>) {
  //         switch (action) {
  //         /* Translate */
  //         case SceneAction::kTranslateX:
  //           Lg::Log()->Trace("Model move X to: " + std::to_string(arg) +
  //           "\n"); pcontroller_->SetTransRates(arg); break;
  //         case SceneAction::kTranslateY:
  //           Lg::Log()->Trace("Model move Y to: " + std::to_string(arg) +
  //           "\n"); pcontroller_->TranslateToY(arg); break;
  //         case SceneAction::kTranslateZ:
  //           Lg::Log()->Trace("Model move Z to: " + std::to_string(arg) +
  //           "\n"); pcontroller_->TranslateToZ(arg); break;
  //         /* Rotate */
  //         case SceneAction::kRotateX:
  //           Lg::Log()->Trace("Model rotate X to: " + std::to_string(arg) +
  //                            "\n");
  //           pcontroller_->SetRotAngles(arg);
  //           break;
  //         case SceneAction::kRotateY:
  //           Lg::Log()->Trace("Model rotate Y to: " + std::to_string(arg) +
  //                            "\n");
  //           pcontroller_->RotateToY(arg);
  //           break;
  //         case SceneAction::kRotateZ:
  //           Lg::Log()->Trace("Model rotate Z to: " + std::to_string(arg) +
  //                            "\n");
  //           pcontroller_->RotateToZ(arg);
  //           break;
  //         /* Scale */
  //         case SceneAction::kScale:
  //           Lg::Log()->Trace("Model scale to: " + std::to_string(arg) +
  //           "\n"); pcontroller_->SetScaleRate(arg); break;
  //         /* Vertexes */
  //         case SceneAction::kVertexSize:
  //           // std::cout << "Vertex size to: " << arg << "\n";
  //           pcontroller_->SetVertexSz(arg);
  //           break;
  //         /* Edges */
  //         case SceneAction::kEdgeThickness:
  //           // std::cout << "Edge thickness to: " << arg << "\n";
  //           pcontroller_->SetEdgeSz(arg);
  //           break;
  //
  //         default:
  //           /* Write Error to log */
  //           break;
  //         }
  //       } else if constexpr (std::is_same_v<T, QColor>) {
  //         switch (action) {
  //         /* Vertexes */
  //         case SceneAction::kVertexColor:
  //           // std::cout << "Vertex color to: (" << arg.red() << ", "
  //           //           << arg.green() << ", " << arg.blue() << ")\n";
  //           pcontroller_->SetVertClr(arg.red(), arg.green(), arg.blue());
  //           break;
  //         /* Edges */
  //         case SceneAction::kEdgeColor:
  //           // std::cout << "Edge color to: (" << arg.red() << ", " <<
  //           // arg.green()
  //           //           << ", " << arg.blue() << ")\n";
  //           //
  //           pcontroller_->SetEdgeClr(arg.red(), arg.green(), arg.blue());
  //           break;
  //         case SceneAction::kBackgroundColor:
  //           // std::cout << "Background color to: (" << arg.red() << ", "
  //           //           << arg.green() << ", " << arg.blue() << ")\n";
  //           pcontroller_->SetBckgClr(arg.red(), arg.green(),
  //                                            arg.blue());
  //           break;
  //         default:
  //           /* Write Error to log */
  //           break;
  //         }
  //       } else if constexpr (std::is_same_v<T, QString>) {
  //         switch (action) {
  //         /* Open file */
  //         case SceneAction::kOpenFile:
  //           Lg::Log()->Info("Попытка открытия файла: " + arg.toStdString());
  //
  //           pcontroller_->BuildObject(arg.toStdString());
  //           OnObjectStartBuild();
  //           break;
  //
  //         default:
  //           /* Write Error to log */
  //           break;
  //         }
  //       } else if constexpr (std::is_same_v<T, VertexStyle> ||
  //                            std::is_same_v<T, EdgeStyle>) {
  //         switch (action) {
  //         /* Vertexes */
  //         case SceneAction::kVertexStyle:
  //           // std::cout << "Vertex style to: " << static_cast<int>(arg) <<
  //           // "\n";
  //           pcontroller_->SetVertStyle(static_cast<int>(arg));
  //           break;
  //         /* Edges */
  //         case SceneAction::kEdgeStyle:
  //           // std::cout << "Edge style to: " << static_cast<int>(arg) <<
  //           "\n"; pcontroller_->SetEdgeStyle(static_cast<int>(arg)); break;
  //
  //         default:
  //           /* Write Error to log */
  //           break;
  //         }
  //       } else if constexpr (std::is_same_v<T, ProjectionType>) {
  //         std::cout << GetEnumName<SceneAction::kProjection>()
  //                   << " to: " << static_cast<int>(arg) << "\n";
  //       } else if constexpr (std::is_same_v<T, RenderType>) {
  //         std::cout << GetEnumName<SceneAction::kRender>()
  //                   << " to: " << static_cast<int>(arg) << "\n";
  //       }
  //     },
  //     data);
}

}  // namespace s21
