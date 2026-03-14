#include "object_viewer_widget.h"
#include <qvectornd.h>

void s21::ObjectViewerWidget::LoadShaders() {
  const char *vertex_shader_source = R"(
      #version 330 core
      // #version 440 core
      // #version 450 core
      layout (location = 0) in vec3 aPos;
      void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
      }
    )";

  const char *fragment_shader_source = R"(
      #version 330 core
      // #version 440 core
      // #version 450 core
      out vec4 FragColor;
      uniform vec4 uColor;

      void main() {
        FragColor = uColor;
      }
    )";

  QOpenGLShader vertex_shader(QOpenGLShader::Vertex);
  if (!vertex_shader.compileSourceCode(vertex_shader_source)) {
    qWarning() << "Vertex shader compilation failed:" << vertex_shader.log();
  }

  QOpenGLShader fragment_shader(QOpenGLShader::Fragment);
  if (!fragment_shader.compileSourceCode(fragment_shader_source)) {
    qWarning() << "Fragment shader compilation failed:"
               << fragment_shader.log();
  }

  m_shader_program_->addShader(&vertex_shader);
  m_shader_program_->addShader(&fragment_shader);
  if (!m_shader_program_->link()) {
    qWarning() << "Shader program link failed:" << m_shader_program_->log();
  }

  m_shader_program_->bind();
  m_shader_program_->setUniformValue("uColor", uColor_);
  m_shader_program_->release();
}
