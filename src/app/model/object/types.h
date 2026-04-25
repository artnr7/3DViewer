#ifndef TYPES_H_
#define TYPES_H_
#include <vector>

#include "../../api/primitives.h"

namespace s21 {

#define THREE_DIMENSIONAL 3

enum TokenID { VerticeID, TextureID, NormalID };

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

};  // namespace s21

#endif
