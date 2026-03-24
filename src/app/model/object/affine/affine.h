#ifndef AFFINE_H_
#define AFFINE_H_

#include "../../api/primitives.h"

namespace s21 {
class Object;

class Affine {
 public:
  // Translate
  void SetTransX(float);
  void SetTransY(float);
  void SetTransZ(float);

  void AddTransX(float);
  void AddTransY(float);
  void AddTransZ(float);

  void SetScale(float);
  void AddScale(float);

  void SetRotX(float);
  void SetRotY(float);
  void SetRotZ(float);

  void AddRotX(float);
  void AddRotY(float);
  void AddRotZ(float);

  void UpdGLVertices();
  void RTS();
  void RotMat();

  void Multiply();

 private:  // VARIABLES
  Object& obj_;
  //
  mat4 mat_trans_{};
  mat4 mat_scale_{};

  float x_{}, y_{}, z_{};

  mat4 mat_proj_{};

  mat4 mat_rot_{};

  mat4 mat_rot_x_{};
  mat4 mat_rot_y_{};
  mat4 mat_rot_z_{};

  mat4 rts_{};

  float fov_ = 1.2f;
  float aspect_ = 12.0f / 9.0f;
  float near_ = 0.1f;
  float far_ = 100.0f;

 public:
  Affine() = delete;
  explicit Affine(Object& obj) : obj_(obj) {
    mat_proj_.SetPerspective(fov_, aspect_, near_, far_);
  }
};

}  // namespace s21
#endif
