#include "../object_class.hpp"

void s21::Object::Combination() {}

void s21::Object::MVP() { mvp_ = m_modelview_ * m_projection; }

void s21::Object::ModelView(QVector3D &vec) {
  m_modelview_.setToIdentity();
  // m_model = m_translate  * m_rotate * m_scale

  m_modelview_.setToIdentity();
  m_modelview_.translate(vec); // указываем на какое расстояние перенести вектор
  m_modelview_.rotate()
}