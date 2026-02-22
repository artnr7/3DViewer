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

// Vertices
struct Points {
private:
  struct Vertices {
  private:
    struct VerticeMap {
      PolyPcInT i;
      CoordT x;
      CoordT y;
      CoordT z;
      friend class Object;
    };

  public:
    std::vector<VerticeMap> vertice_maps;
    CoordT min_x;
    CoordT max_x;
    CoordT min_y;
    CoordT max_y;
    CoordT min_z;
    CoordT max_z;
    friend class Object;
  };

  struct Textures {
  private:
    struct TextureMap {
      PolyPcInT i;
      CoordT u;
      CoordT v;
      CoordT w = 0;
    };

  public:
    std::vector<TextureMap> texture_maps;
    // CoordT min_x;
    // CoordT max_x;
    // CoordT min_y;
    // CoordT max_y;
    // CoordT min_z;
    // CoordT max_z;
  };

  struct Normals {
  private:
    struct NormalMap {
      PolyPcInT i;
      CoordT x;
      CoordT y;
      CoordT z;
    };

  public:
    std::vector<NormalMap> texture_maps;
    // CoordT min_x;
    // CoordT max_x;
    // CoordT min_y;
    // CoordT max_y;
    // CoordT min_z;
    // CoordT max_z;
  };

public:
  Vertices vertices;
  Textures textures;
  Normals normals;
  friend class Object;
};

// Face
struct Faces {
private:
  struct FaceMap {
  private:
    struct MapEl {
      PolyPcInT vert_i;
      PolyPcInT txr_i;
      PolyPcInT norl_i;
      friend class Object;
    };

  public:
    PolyPcInT i;
    std::vector<MapEl> map;
    friend class Object;
  };

public:
  std::vector<FaceMap> face_maps;
  size_t dimension_qty = DIMENSION_QTY;
  friend class Object;
};

}; // namespace s21
