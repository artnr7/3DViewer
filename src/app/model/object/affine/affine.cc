// #include <glm/ext/matrix_clip_space.hpp>  // glm::perspective
// #include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate,
// glm::scale #include <glm/ext/scalar_constants.hpp>  // glm::pi #include
// <glm/mat4x4.hpp>                // glm::mat4 #include <glm/vec3.hpp> //
// glm::vec3 #include <glm/vec4.hpp>                  // glm::vec4

#include "affine.h"

#include "../../utils/logger.h"
#include "../object.h"

namespace s21 {
// Translate
void Affine::SetTransX(float x) { mat_trans_.TranslateToX(x); }
void Affine::SetTransY(float y) { mat_trans_.TranslateToY(y); }
void Affine::SetTransZ(float x) { mat_trans_.TranslateToZ(x); }

void Affine::AddTransX(float x) { mat_trans_.AddTransX(x); }
void Affine::AddTransY(float y) { mat_trans_.AddTransY(y); }
void Affine::AddTransZ(float z) { mat_trans_.AddTransZ(z); }

// Scale
void Affine::SetScale(float scl_rt) { mat_scale_.SetScale(scl_rt); }
void Affine::AddScale(float scl_rt) { mat_scale_.AddScale(scl_rt); }

// clang-format off
void Affine::SetRotX(float x) { x_ = x; mat_rot_x_.RotX(x_); }
void Affine::SetRotY(float y) { y_ = y; mat_rot_y_.RotY(y_); }
void Affine::SetRotZ(float z) { z_ = z; mat_rot_z_.RotZ(z_);}

void Affine::AddRotX(float x) { x_ += x; mat_rot_x_.RotX(x_); }
void Affine::AddRotY(float y) { y_ += y; mat_rot_y_.RotY(y_); }
void Affine::AddRotZ(float z) { z_ += z; mat_rot_z_.RotZ(z_); }
// clang-format on

void Affine::UpdGLVertices() {
  RTS();
  Multiply();
}

void Affine::RotMat() { mat_rot_ = mat_rot_x_ * mat_rot_y_ * mat_rot_z_; }

void Affine::RTS() {
  rts_.SetZero();

  RotMat();
  rts_ = mat_proj_ * mat_trans_ * mat_scale_ * mat_rot_;
  // rts_.Print();
}

void Affine::Multiply() {
  Lg::Log()->Trace("Object::Affine::" + std::string(__func__));
  uint32_t i = 0;
  for (auto it = obj_.vertices_.maps.begin(); it != obj_.vertices_.maps.end();
       ++it) {
    vec4 v = rts_ * *it;

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
  obj_.init_f_ = false;
}

}  // namespace s21
