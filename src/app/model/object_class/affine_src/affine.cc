#include "object_class.h"

namespace s21 {
// To
void Object::Affine::TranslateToX(float x) { mat_trans_.TranslateToX(x); }

void Object::Affine::TranslateToY(float x) { mat_trans_.TranslateToY(x); }

void Object::Affine::TranslateToZ(float x) { mat_trans_.TranslateToZ(x); }

// On
void Object::Affine::TranslateOnX(float x) {
  mat_trans_.TranslateOn(vec4{x, 0.0f, 0.0f});
}

void Object::Affine::TranslateOnY(float x) {
  mat_trans_.TranslateOn(vec4{0.0f, x, 0.0f});
}

void Object::Affine::TranslateOnZ(float x) {
  mat_trans_.TranslateOn(vec4{0.0f, x, 0.0f});
}

// Scale
void Object::Affine::Scale(float x) { mat_scale_.ScaleTo(x); }

void Object::Affine::RotateX(float x) { mat_rot_x_.RotateX(x); }
void Object::Affine::RotateY(float x) { mat_rot_y_.RotateY(x); }
void Object::Affine::RotateZ(float x) { mat_rot_z_.RotateZ(x); }

void Object::Affine::RotMat() {
  mat_rot_ = mat_rot_x_ * mat_rot_y_ * mat_rot_z_;
}

void Object::Affine::RTS() {
  rts_.SetZero();

  mat_rot_ = mat_rot_x_ * mat_rot_y_ * mat_rot_z_;
  rts_ = mat_trans_ * mat_scale_ * mat_rot_;
  // rts_ = mat_rotate_;
  // rts_.Print();
}

void Object::Affine::Multiply() {
  Lg::Log()->Trace("Object::Affine::" + std::string(__func__));
  uint32_t i = 0;
  for (auto it = obj_.vertices_.maps.begin(); it != obj_.vertices_.maps.end();
       ++it) {
    // it->Print();
    vec4 v = rts_ * *it;
    // v.Print();

    if (obj_.init_f_) {
      obj_.glvertices_.push_back(v.x);
      obj_.glvertices_.push_back(v.y);
      obj_.glvertices_.push_back(v.z);
    } else {
      obj_.glvertices_[i] = v.x;
      obj_.glvertices_[i + 1] = v.y;
      obj_.glvertices_[i + 2] = v.z;
      i += 3;
    }
  }
  // obj_.PrintGLVertices();
  obj_.init_f_ = false;
}

} // namespace s21
