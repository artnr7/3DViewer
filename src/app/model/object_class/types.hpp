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
typedef struct {
private:
  typedef struct {
  private:
    typedef struct {
      PolyPcInT i;
      CoordT x;
      CoordT y;
      CoordT z;
      friend class Object;
    } VerticeMap;

  public:
    std::vector<VerticeMap> vertice_maps;
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int min_z;
    int max_z;
    friend class Object;
  } Vertices;

  typedef struct {
  private:
    typedef struct {
      PolyPcInT i;
      CoordT u;
      CoordT v;
      CoordT w = 0;
    } TextureMap;

  public:
    std::vector<TextureMap> texture_maps;
    // int min_x;
    // int max_x;
    // int min_y;
    // int max_y;
    // int min_z;
    // int max_z;
  } Textures;

  typedef struct {
  private:
    typedef struct {
      PolyPcInT i;
      CoordT x;
      CoordT y;
      CoordT z;
    } NormalMap;

  public:
    std::vector<NormalMap> texture_maps;
    // int min_x;
    // int max_x;
    // int min_y;
    // int max_y;
    // int min_z;
    // int max_z;
  } Normals;

public:
  Vertices vertices;
  Textures textures;
  Normals normals;
  friend class Object;
} Vertices;

// Face
typedef struct {
private:
  typedef struct {
  private:
    typedef struct {
      PolyPcInT vert_i;
      PolyPcInT txr_i;
      PolyPcInT norl_i;
      friend class Object;
    } MapEl;

  public:
    PolyPcInT i;
    std::vector<MapEl> map;
    friend class Object;
  } FaceMap;

public:
  std::vector<FaceMap> face_maps;
  size_t dimension_qty = DIMENSION_QTY;
  friend class Object;
} Faces;

}; // namespace s21