#include "object_class.hpp"

// mvp_ = m_projection * m_view_ *  m_model_
// m_model = m_translate  * m_rotate * m_scale

QMatrix4x4 &s21::Object::GetModelMatrix() { return m_model_; }

void s21::Object::MatrixTranslate(QVector3D &vec) {
  SetToIdentityIfNot(m_model_);
  // указываем на какое расстояние перенести вектор ↓
  m_model_.translate(vec);
}

void s21::Object::MatrixRotate(float &angle, QVector3D &vec) {
  SetToIdentityIfNot(m_model_);
  m_model_.rotate(angle, vec);
}

void s21::Object::MatrixScale(float &mult) {
  SetToIdentityIfNot(m_model_);
  m_model_.scale(mult);
}

void s21::Object::SetToIdentityIfNot(QMatrix4x4 &mtx) {
  if (not mtx.isIdentity()) {
    mtx.setToIdentity();
  }
}