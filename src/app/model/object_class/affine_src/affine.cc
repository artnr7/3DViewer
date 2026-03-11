#include "object_class.h"

namespace s21 {
void Object::Affine::Translate(const uint8_t shift, float arg) {
  Lg::Log()->Info("Object::Affine" + std::string(__func__));
  // TODO(sundaeka): проверка на размера массива, должен быть минимум 3 и кратен
  // 3
  for (auto it = obj_.glvertices_.begin(); it != obj_.glvertices_.end();
       it += 3) {
    *(it + shift) += arg;
  }
}

void Object::Affine::TranslateX(float x) {
  Lg::Log()->Info("Object::Affine" + std::string(__func__));
  Translate(0, x);
}

void Object::Affine::TranslateY(float y) { Translate(1, y); }
void Object::Affine::TranslateZ(float z) { Translate(2, z); }

void Object::Affine::TranslateOnX(float x) {
  mat_trans_.TranslateOn(vec4{x, 0.0f, 0.0f});
}

void Object::Affine::TranslateOnY(float x) {
  mat_trans_.TranslateOn(vec4{0.0f, x, 0.0f});
}

void Object::Affine::RotateX() {}

void Object::Affine::RTS() {
  rts_.SetZero();

  rts_ = mat_trans_ * mat_scale_ * mat_rotate_;
  // rts_.Print();
}

void Object::Affine::Multiply() {
  uint32_t i = 0;
  for (auto it = obj_.vertices_.maps.begin(); it != obj_.vertices_.maps.end();
       ++it) {
    // it->Print();
    vec4 v = rts_ * *it;
    // v.Print();
    obj_.glvertices_[i] = v.x;
    obj_.glvertices_[i + 1] = v.y;
    obj_.glvertices_[i + 2] = v.z;
    i += 3;
  }
  // obj_.PrintGLVertices();
}

} // namespace s21
