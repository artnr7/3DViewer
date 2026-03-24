#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

namespace s21 {

using Str = std::string;
using CoordT = float;
using IndT = uint32_t;

// Vec4
struct vec4 {
  CoordT x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
  vec4() = default;
  vec4(CoordT x, CoordT y, CoordT z, CoordT w = 1.0f)
      : x(x), y(y), z(z), w(w) {}

  void SetZero() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
  }

  CoordT& operator[](size_t i) {
    switch (i) {
      case 0:
        return x;
        break;
      case 1:
        return y;
        break;
      case 2:
        return z;
        break;
      case 3:
        return w;
        break;
      default:
        throw std::invalid_argument("You can't use this index");
        break;
    }
  }

  void Print() const {
    std::cout << "vec\n---------------------------\n";
    std::cout << x << " " << y << " " << z << " " << w << "\n\n";
  }
};

// Mat4
struct mat4 {
  std::array<std::array<CoordT, 4>, 4> data{};

  mat4() { SetIdentity(); }

  void TranslateToX(float x) { data[0][3] = x; }
  void TranslateToY(float x) { data[1][3] = x; }
  void TranslateToZ(float x) { data[2][3] = x; }

  void AddTransX(float x) { data[0][3] += x; }
  void AddTransY(float y) { data[1][3] += y; }
  void AddTransZ(float z) { data[2][3] += z; }

  void AddTrans(vec4 v) {
    data[0][3] += v.x;
    data[1][3] += v.y;
    data[2][3] += v.z;
  }

  void SetScale(float scl_rt) {
    data[0][0] = scl_rt;
    data[1][1] = scl_rt;
    data[2][2] = scl_rt;
  }

  void AddScale(float scl_rt) {
    data[0][0] += scl_rt;
    data[1][1] += scl_rt;
    data[2][2] += scl_rt;
  }

 private:
  static std::pair<float, float> CosSin(float alpha) {  // conditionaly static
    auto d_x = static_cast<double>(alpha);
    auto c = static_cast<float>(cos(d_x));
    auto s = static_cast<float>(sin(d_x));
    return std::make_pair(c, s);
  }

 public:
  void RotX(float x) {
    auto [c, s] = CosSin(x);

    data[0] = {1.0f, 0.0f, 0.0f, 0.0f};
    data[1] = {0.0f, c, -s, 0.0f};
    data[2] = {0.0f, s, c, 0.0f};
    data[3] = {0.0f, 0.0f, 0.0f, 1.0f};
  }

  void RotY(float x) {
    auto [c, s] = CosSin(x);

    data[0] = {c, 0.0f, s, 0.0f};
    data[1] = {0.0f, 1.0f, 0.0f, 0.0f};
    data[2] = {-s, 0.0f, c, 0.0f};
    data[3] = {0.0f, 0.0f, 0.0f, 1.0f};
  }

  void RotZ(float x) {
    auto [c, s] = CosSin(x);

    data[0] = {c, -s, 0.0f, 0.0f};
    data[1] = {s, c, 0.0f, 0.0f};
    data[2] = {0.0f, 0.0f, 1.0f, 0.0f};
    data[3] = {0.0f, 0.0f, 0.0f, 1.0f};
  }

  mat4 operator*(mat4& m) {
    mat4 res{};
    res.SetZero();

    Multiply(*this, m, res);
    return res;
  }

  vec4 operator*(vec4& v) {
    vec4 res{};
    res.SetZero();

    Multiply(*this, v, res);
    return res;
  }

 private:
  std::array<CoordT, 4>& operator[](size_t i) { return data[i]; }

  void Multiply(mat4& m1, mat4& m2, mat4& res) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 4; ++k) {
          res[i][j] += m1[i][k] * m2[k][j];
        }
      }
    }
  }

  void Multiply(mat4& m, vec4& v, vec4& res) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        res[i] += m[i][j] * v[j];
      }
    }
  }

 public:
  void SetIdentity() {
    for (uint8_t i = 0; i < 4; ++i) {
      data[i][i] = 1.0f;
    }
  }

  void SetZero() {
    for (uint8_t i = 0; i < 4; ++i) {
      for (uint8_t j = 0; j < 4; ++j) {
        data[i][j] = 0.0f;
      }
    }
  }

  void SetPerspective(float fov, float aspect, float near, float far) {
    SetZero();
    auto t = static_cast<float>(tan(fov / 2.0f));

    data[0][0] = 1.0f / (aspect * t);
    data[1][1] = 1.0f / t;
    data[2][2] = -((far + near) / (far - near));
    data[2][3] = -1.0f;
    data[3][2] = -((2.0f * far * near) / (far - near));
  }

  void Print() {
    std::cout << "mat4\n---------------------------\n";
    for (auto row : data) {
      for (auto el : row) {
        std::cout << el << " ";
      }
      std::cout << "\n";
    }
  }
};

struct Angles {
  float x, y, z;
};

struct Rates {
  float x, y, z;
};

struct Color {
  uint8_t x, y, z;
  void Print() const {
    std::cout << static_cast<int>(x) << " " << static_cast<int>(y) << " "
              << static_cast<int>(z) << std::endl;
  }
};

}  // namespace s21
#endif
