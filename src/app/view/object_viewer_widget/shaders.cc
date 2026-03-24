#include <qvectornd.h>

#include "obj_v_wid.h"

void s21::ObjectViewerWidget::LoadShaders() {
  const char* vertex_shader_source = R"(
      #version 450 core
      // #version 440 core
      // #version 450 core

      layout (location = 0) in vec3 aPos;

      flat out vec3 startPos;
      out vec3 vertPos;

      void main() {
        vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        gl_Position = pos;
        vertPos = pos.xyz / pos.w;
        startPos = vertPos;
      }
    )";

  const char* fragment_shader_source = R"(
      #version 450 core
      // #version 440 core
      // #version 450 core
      
      flat in vec3 startPos;
      in vec3 vertPos;

      out vec4 FragColor;

      uniform vec4 uMeshClr;

      uniform vec2 u_resolution;
      uniform float u_dashSize;
      uniform float u_gapSize;

      void main() {
        vec2 dir = (vertPos.xy-startPos.xy) * u_resolution/2.0;
        float dist = length(dir);

        if (fract(dist / (u_dashSize + u_gapSize)) > u_dashSize / (u_dashSize + u_gapSize))
          discard;
        FragColor = uMeshClr;
      }
    )";
  // if (length(gl_PointCoord - vec2(0.5)) > 0.5)
  //     discard;
  //   для кругов через шейдер

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
  m_shader_program_->setUniformValue(uMeshClrName_, uEdgeClr_);
  m_shader_program_->setUniformValue("u_resolution", resolution_);
  m_shader_program_->setUniformValue("u_dashSize", dash_sz_);
  m_shader_program_->setUniformValue("u_gapSize", gap_sz_);
  m_shader_program_->release();
}
