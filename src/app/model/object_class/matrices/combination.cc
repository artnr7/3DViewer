#include <qvectornd.h>

#include "../object_class.hpp"

void s21::Object::Combination() {
  MVP();
  QVector4D vec{};
  for (auto &el : vertices_.vertices.vertice_maps) {
    vec = {(float)el.x, (float)el.y, (float)el.z, 1.0};
    vec = mvp_ * vec;
    el.x = vec.x();
    el.y = vec.y();
    el.z = vec.z();
  }
}

void s21::Object::MVP() { mvp_ = m_modelview_ * m_projection; }

// m_model = m_translate  * m_rotate * m_scale

void s21::Object::MatrixTranslate(QVector3D &vec) {
  SetToIdentityIfNot(m_modelview_);
  // указываем на какое расстояние перенести вектор ↓
  m_modelview_.translate(vec);
}

void s21::Object::MatrixRotate(float &angle, QVector3D &vec) {
  SetToIdentityIfNot(m_modelview_);
  m_modelview_.rotate(angle, vec);
}

void s21::Object::MatrixScale(float &mult) {
  SetToIdentityIfNot(m_modelview_);
  m_modelview_.scale(mult);
}

void s21::Object::LookAt(const QVector3D &eye, const QVector3D &center,
                         const QVector3D &up) {
  SetToIdentityIfNot(m_modelview_);
  m_modelview_.lookAt(eye, center, up);
}

void s21::Object::PerspectiveProjectionMatrix(const int &w, const int &h) {
  SetToIdentityIfNot(m_projection);
  float angle = 45.0f;
  float near_plane = 0.01f;
  float far_plane = 100.0f;

  m_projection.perspective(angle, w / float(h), near_plane, far_plane);
}

void s21::Object::OrthoProjectionMatrix() {
  SetToIdentityIfNot(m_projection);
  // float angle = 45.0f;
  float near_plane = 0.01f;
  float far_plane = 100.0f;

  m_projection.ortho(-0.005523, 0.005523, -0.004142, 0.004142, near_plane,
                     far_plane);
}

void s21::Object::SetToIdentityIfNot(QMatrix4x4 &mtx) {
  if (not mtx.isIdentity()) {
    mtx.setToIdentity();
  }
}