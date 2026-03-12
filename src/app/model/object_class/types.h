#include "iostream"
#include <array>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>

namespace s21 {

#define THREE_DIMENSIONAL 3

enum TokenID { VerticeID, TextureID, NormalID };

using CoordT = float;
using IndT = uint32_t;

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

  CoordT &operator[](size_t i) {
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

  void Print() {
    std::cout << "vec\n---------------------------\n";
    std::cout << x << " " << y << " " << z << " " << w << "\n\n";
  }
};

struct mat4 {
  std::array<std::array<CoordT, 4>, 4> data{};

  mat4() { SetIdentity(); }

  void TranslateToX(float x) { data[0][3] = x; }
  void TranslateToY(float x) { data[1][3] = x; }
  void TranslateToZ(float x) { data[2][3] = x; }

  void TranslateOn(vec4 v) {
    data[0][3] += v.x;
    data[1][3] += v.y;
    data[2][3] += v.z;
  }

  void ScaleTo(float x) {
    data[0][0] = x;
    data[1][1] = x;
    data[2][2] = x;
  }

  void RotateX(float x) {
    float d_x = static_cast<double>(x);
    float c = static_cast<float>(cos(d_x));
    float s = static_cast<float>(sin(d_x));

    data[0] = {1.0f, 0.0f, 0.0f, 0.0f};
    data[1] = {0.0f, c, -s, 0.0f};
    data[2] = {0.0f, s, c, 0.0f};
    data[3] = {0.0f, 0.0f, 0.0f, 1.0f};
  }

  void RotateY(float x) {
    float d_x = static_cast<double>(x);
    float c = static_cast<float>(cos(d_x));
    float s = static_cast<float>(sin(d_x));

    data[0] = {c, 0.0f, s, 0.0f};
    data[1] = {0.0f, 1.0f, 0.0f, 0.0f};
    data[2] = {-s, 0.0f, c, 0.0f};
    data[3] = {0.0f, 0.0f, 0.0f, 1.0f};
  }

  void RotateZ(float x) {
    float d_x = static_cast<double>(x);
    float c = static_cast<float>(cos(d_x));
    float s = static_cast<float>(sin(d_x));

    data[0] = {c, -s, 0.0f, 0.0f};
    data[1] = {s, c, 0.0f, 0.0f};
    data[2] = {0.0f, 0.0f, 1.0f, 0.0f};
    data[3] = {0.0f, 0.0f, 0.0f, 1.0f};
  }
  mat4 operator*(mat4 &m) {
    mat4 res{};
    res.SetZero();

    Multiply(*this, m, res);
    return res;
  }

  vec4 operator*(vec4 &v) {
    vec4 res{};
    res.SetZero();

    Multiply(*this, v, res);
    return res;
  }

private:
  std::array<CoordT, 4> &operator[](size_t i) { return data[i]; }

  void Multiply(mat4 &m1, mat4 &m2, mat4 &res) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 4; ++k) {
          res[i][j] += m1[i][k] * m2[k][j];
        }
      }
    }
  }

  void Multiply(mat4 &m, vec4 &v, vec4 &res) {
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

struct MinMax {
  CoordT min_x, max_x, min_y, max_y, min_z, max_z;
};

// Vertices
using VertMaps = std::vector<vec4>;

struct Vertices {
  VertMaps maps;
  MinMax mnx;
};

// Textures
// struct TextureMap {
//   CoordT u, v, w = 0;
// };
//
// struct Textures {
//   std::vector<TextureMap> maps;
//   MinMax mnx;
// };

// Normals
// struct NormalMap {
//   CoordT x, y, z;
// };
//
// struct Normals {
//   std::vector<NormalMap> maps;
//   MinMax minmax;
// };

// Faces ---
struct MapEl {
  IndT vert_i;
  IndT txr_i;
  IndT norl_i;
};

using FaceMap = std::vector<MapEl>;

using Faces = std::vector<FaceMap>;

}; // namespace s21
