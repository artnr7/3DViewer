#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// #include <QOpenGLExtraFunctions>
// #include <QOpenGLVertexArrayObject>
#include <GL/glu.h>

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QtGui>
#include <QtOpenGL>

namespace s21 {
class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
public:
  MainWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {
    setWindowTitle("3DViewer");
    setGeometry(400, 200, 800, 600);
  }

protected:
  void initializeGL() override {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

    const char *vertex_shader_source = R"(
      #version 450 core
      layout (location = 0) in vec3 aPos;
      void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
      }
    )";

    const char *fragment_shader_source = R"(
      #version 450 core
      out vec4 FragColor;
      void main() {
        FragColor = vec4(0.0f, 0.0f, 0.2f, 1.0f);
      }
    )";

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // projLoc = glGetUniformLocation(shader_program, "projection");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Создаем VAO и VBO один раз
    GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                          0.0f,  0.0f,  0.5f, 0.0f};

    f = context()->extraFunctions();

    f->glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    f->glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
  }

  void resizeGL(int w, int h) override {
    glViewport(0, 0, w, h);

    // float aspect = static_cast<float>(w) / static_cast<float>(h);
    // gluPerspective(45.0, aspect, 0.1, 100.0);

    m_projection.setToIdentity();
    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
  }

  void paintGL() override {

    m_modelview.setToIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program);
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, m_projection.constData());

    f->glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    f->glBindVertexArray(0);
  }

private:
  QMatrix4x4 m_modelview;
  QMatrix4x4 m_projection;
  // GLint projLoc;
  // QOpenGLVertexArrayObject m_vao;
  // QOpenGLBuffer m_vbo;
  // QOpenGLShaderProgram *m_program;
  // QOpenGLShader *m_shader;
  // QOpenGLTexture *m_texture;
  GLuint shader_program;
  GLuint VBO;
  GLuint VAO;
  QOpenGLExtraFunctions *f;
};
} // namespace s21

#endif
