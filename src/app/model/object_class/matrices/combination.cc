#include <qvectornd.h>

#include "../object_class.hpp"

void s21::Object::Combination() {
  QVector4D vec{};
  for (auto &el : vertices_.vertices.vertice_maps) {
    vec = {(float)el.x, (float)el.y, (float)el.z, 1.0};
  }

  vec = mvp_ * vec;
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

void s21::Object::ProjectionMatrix() {
  SetToIdentityIfNot(m_projection);

  m_projection.perspective(float verticalAngle, float aspectRatio,
                           float nearPlane, float farPlane)
}
void s21::Object::SetToIdentityIfNot(QMatrix4x4 &mtx) {
  if (not mtx.isIdentity()) {
    mtx.setToIdentity();
  }
}