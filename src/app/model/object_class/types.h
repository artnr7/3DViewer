#include <array>
#include <cmath>
#include <cstdint>
#include <string>
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
      : x(x), y(y), z(z), w(w) {};
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
