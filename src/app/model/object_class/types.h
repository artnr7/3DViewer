#include <array>
#include <cmath>
#include <cstdint>
#include <glm/ext/vector_float4.hpp>
#include <string>
#include <utility>
#include <vector>

namespace s21 {

#define DIMENSION_QTY 3

enum TokenID { VerticeID, TextureID, NormalID };

using CoordT = float;
using IndT = uint32_t;

using vec3 = std::array<CoordT, 3>;

struct vec4 {
  std::array<CoordT, 4> data_{0.0f, 0.0f, 0.0f, 1.0f};
  vec4() = default;
  vec4(CoordT x, CoordT y, CoordT z, CoordT w = 1.0f) : data_{x, y, z, w} {};
  CoordT &x = data_[0];
  CoordT &y = data_[1];
  CoordT &z = data_[2];
  CoordT &w = data_[3];
};

using vert_map = std::pair<IndT, vec4>;

struct MinMax {
  CoordT min_x, max_x, min_y, max_y, min_z, max_z;
};

// Vertices
struct Vertices {
  std::vector<vert_map> maps;
  MinMax mnx;
};

// Textures
struct TextureMap {
  IndT i;
  CoordT u, v, w = 0;
};

struct Textures {
  std::vector<TextureMap> texture_maps;
  MinMax mnx;
};

// Normals
struct NormalMap {
  IndT i;
  CoordT x, y, z;
};

struct Normals {
  std::vector<NormalMap> texture_maps;
  MinMax minmax;
};

// Faces ---
struct MapEl {
  IndT vert_i;
  IndT txr_i;
  IndT norl_i;
};

struct FaceMap {
  IndT i;
  std::vector<MapEl> data;
};

using Faces = std::vector<FaceMap>;

}; // namespace s21
