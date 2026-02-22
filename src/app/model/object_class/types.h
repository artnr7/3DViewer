#include <string>
#include <vector>

namespace s21 {

enum ParseStatus {
  Good,
  Invalid,

  NoVertices,
  InvalidVertice,

  NoFaces,
  InvalidFace,

  NotEnoughVertices,
};

enum TokenID { VerticeID, TextureID, NormalID };

#define DIMENSION_QTY 3
using CoordT = long double;
using PolyPcInT = long int;

struct VerticeMap {
  PolyPcInT i;
  CoordT x;
  CoordT y;
  CoordT z;
};
struct Vertices {
  std::vector<VerticeMap> vertice_maps;
  CoordT min_x;
  CoordT max_x;
  CoordT min_y;
  CoordT max_y;
  CoordT min_z;
  CoordT max_z;
};
//
struct TextureMap {
  PolyPcInT i;
  CoordT u;
  CoordT v;
  CoordT w = 0;
};
struct Textures {
  std::vector<TextureMap> texture_maps;
  // CoordT min_x;
  // CoordT max_x;
  // CoordT min_y;
  // CoordT max_y;
  // CoordT min_z;
  // CoordT max_z;
};

// Normals
struct NormalMap {
  PolyPcInT i;
  CoordT x;
  CoordT y;
  CoordT z;
};
struct Normals {
  std::vector<NormalMap> texture_maps;
  // CoordT min_x;
  // CoordT max_x;
  // CoordT min_y;
  // CoordT max_y;
  // CoordT min_z;
  // CoordT max_z;
};

// Points ---
struct Points {
  Vertices vertices;
  Textures textures;
  Normals normals;
};

// Faces ---
struct MapEl {
  PolyPcInT vert_i;
  PolyPcInT txr_i;
  PolyPcInT norl_i;
};

struct FaceMap {
  PolyPcInT i;
  std::vector<MapEl> map;
};

struct Faces {
  std::vector<FaceMap> face_maps;
  size_t dimension_qty = DIMENSION_QTY;
};

}; // namespace s21
