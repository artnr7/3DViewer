#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>  // glm::perspective
#include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>  // glm::pi
#include <glm/mat4x4.hpp>                // glm::mat4
#include <glm/vec3.hpp>                  // glm::vec3
#include <glm/vec4.hpp>                  // glm::vec4

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
  mat_trans_.TranslateOn(vec4{0.0f, 0.0f, x});
}

// Scale
void Object::Affine::Scale(float x) { mat_scale_.ScaleTo(x); }
void Object::Affine::AddScale(float x) { mat_scale_.ScaleOn(x); }

void Object::Affine::RotateToX(float x) {
  x_ = x;
  mat_rot_x_.RotateX(x_);
}

void Object::Affine::RotateToY(float x) {
  y_ = x;
  mat_rot_y_.RotateY(y_);
}

void Object::Affine::RotateToZ(float x) {
  z_ = x;
  mat_rot_z_.RotateZ(z_);
}

void Object::Affine::RotateOnX(float x) {
  x_ += x;
  mat_rot_x_.RotateX(x_);
}
void Object::Affine::RotateOnY(float x) {
  y_ += x;
  mat_rot_y_.RotateY(y_);
}
void Object::Affine::RotateOnZ(float x) {
  z_ += x;
  mat_rot_z_.RotateZ(z_);
}

void Object::Affine::RotMat() {
  mat_rot_ = mat_rot_x_ * mat_rot_y_ * mat_rot_z_;
}

void Object::Affine::UpdateGLVertices() {
  RTS();
  Multiply();
}

void Object::Affine::RTS() {
  rts_.SetZero();

  mat4 proj{};
  proj.SetZero();

  auto fov = 1.2f;
  auto aspect = 12.0f / 9.0f;
  auto near = 0.1f;
  auto far = 100.0f;
  proj.data[0][0] = 1.0f / (aspect * tan(fov / 2));
  proj.data[1][1] = 1.0f / tan(fov / 2);
  proj.data[2][2] = -((far + near) / (far - near));
  proj.data[2][3] = -1;
  proj.data[3][2] = -((2 * far * near) / (far - near));

  mat_rot_ = mat_rot_x_ * mat_rot_y_ * mat_rot_z_;
  rts_ = proj * mat_trans_ * mat_scale_ * mat_rot_;
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

}  // namespace s21
