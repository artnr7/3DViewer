#include "view.h"

#include <string>
#include <vector>

#include "config.h"
#include "enum.h"
#include "logger.h"

namespace s21 {

View::View(Controller *controller, QWidget *parent)
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
}

void View::SetupConnections() {
  Lg::Log()->Info("View::" + std::string(__func__));

  // menu_wid
  // эт когда меню данны в модель посылает
  connect(pmenu_wid_, &MenuWidget::ActionTriggered, this,
          &View::OnActionTriggered);

  // это когда уже запущенный таймер менюшки хочет данные обновить
  connect(menu_wid_update_timer_, &QTimer::timeout, this,
          &View::OnMenuWidgetTimerUpdated);

  // obj_wid
  connect(pobj_v_wid_, &ObjectViewerWidget::ActionGetGLVertices, this,
          &View::OnGetGLVertices);

  connect(pobj_v_wid_, &ObjectViewerWidget::BackgroundColorUpdate, this,
          &View::OnObjectViewerBackgroundUpdated);
}

void View::OnActionTriggered(SceneAction action, ActionData data) {
  // Lg::Log()->Info("View::"+std::string(__func__));

  std::visit(
      [this, action](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, int>) {
          switch (action) {
          /* Translate */
          case SceneAction::kTranslateX:
            std::cout << "Model move X to: " << arg << "\n";
            break;
          case SceneAction::kTranslateY:
            std::cout << "Model move Y to: " << arg << "\n";
            break;
          case SceneAction::kTranslateZ:
            std::cout << "Model move Z to: " << arg << "\n";
            break;
          /* Rotate */
          case SceneAction::kRotateX:
            std::cout << "Model rotate X to: " << arg << "\n";
            break;
          case SceneAction::kRotateY:
            std::cout << "Model rotate Y to: " << arg << "\n";
            break;
          case SceneAction::kRotateZ:
            std::cout << "Model rotate Z to: " << arg << "\n";
            break;
          /* Scale */
          case SceneAction::kScale:
            std::cout << "Model scale to: " << arg << "\n";
            break;
          /* Vertexes */
          case SceneAction::kVertexSize:
            std::cout << "Vertex size to: " << arg << "\n";
            break;
          /* Edges */
          case SceneAction::kEdgeThickness:
            std::cout << "Edge thickness to: " << arg << "\n";
            break;

          default:
            /* Write Error to log */
            break;
          }
        } else if constexpr (std::is_same_v<T, QColor>) {
          switch (action) {
          /* Vertexes */
          case SceneAction::kVertexColor:
            std::cout << "Vertex color to: (" << arg.red() << ", "
                      << arg.green() << ", " << arg.blue() << ")\n";
            break;
          /* Edges */
          case SceneAction::kEdgeColor:
            std::cout << "Edge color to: (" << arg.red() << ", " << arg.green()
                      << ", " << arg.blue() << ")\n";
            break;
          case SceneAction::kBackgroundColor:
            std::cout << "Background color to: (" << arg.red() << ", "
                      << arg.green() << ", " << arg.blue() << ")\n";
            pcontroller_->SetBackgroundColor(arg.red(), arg.green(),
                                             arg.blue());
            break;
          default:
            /* Write Error to log */
            break;
          }
        } else if constexpr (std::is_same_v<T, QString>) {
          switch (action) {
          /* Open file */
          case SceneAction::kOpenFile:
            // auto filename = arg.toStdString();
            Lg::Log()->Info("Попытка открытия файла: " + arg.toStdString());
            pcontroller_->BuildObject(arg.toStdString());
            OnObjectStartBuild();
            break;

          default:
            /* Write Error to log */
            break;
          }
        } else if constexpr (std::is_same_v<T, VertexStyle> ||
                             std::is_same_v<T, EdgeStyle>) {
          switch (action) {
          /* Vertexes */
          case SceneAction::kVertexStyle:
            std::cout << "Vertex style to: " << static_cast<int>(arg) << "\n";
            break;
          /* Edges */
          case SceneAction::kEdgeStyle:
            std::cout << "Edge style to: " << static_cast<int>(arg) << "\n";
            break;

          default:
            /* Write Error to log */
            break;
          }
        } else if constexpr (std::is_same_v<T, ProjectionType>) {
          std::cout << GetEnumName<SceneAction::kProjection>()
                    << " to: " << static_cast<int>(arg) << "\n";
        } else if constexpr (std::is_same_v<T, RenderType>) {
          std::cout << GetEnumName<SceneAction::kRender>()
                    << " to: " << static_cast<int>(arg) << "\n";
        }
      },
      data);
}

} // namespace s21
