#ifndef SETTINGS_PARSER_H_
#define SETTINGS_PARSER_H_

#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <utility>
#include <variant>
#include <vector>

#define SETTINGS_FILE

namespace s21 {

class SettingsParser {

public:
  using factors = std::array<float, 3>;
  using type = uint16_t;
  using val = float;

private:
  enum class Settings {
    RotAngles,
    TransFactors,
    ScaleFactors,

    VertexSz,
    VertexStyle,
    VertexClr,

    EdgeSz,
    EdgeStyle,
    EdgeClr,

    BckgClr,

    Proj,

    Render,

    Filename,
  };
  using JsonVal = std::variant<factors, val, type, std::string>;

  struct ty {
    Settings inner;
    std::string foreign;
    JsonVal json_val;
  };

  std::vector<ty> settings_{
      {Settings::RotAngles, "rotationAngles", factors()},
      {Settings::TransFactors, "translationFactors", factors()},
      {Settings::ScaleFactors, "scaleFactors", factors()},

      {Settings::VertexSz, "vertexSize", val()},
      {Settings::VertexStyle, "vertexStyle", type()},
      {Settings::VertexClr, "vertexClr", factors()},

      {Settings::EdgeSz, "edgeSize", val()},
      {Settings::EdgeStyle, "edgeStyle", type()},
      {Settings::EdgeClr, "edgeColor", factors()},

      {Settings::BckgClr, "backgroundColor", factors()},

      {Settings::Proj, "projectionType", type()},

      {Settings::Render, "renderType", type()},

      {Settings::Filename, "filename", std::string()},
  };

  std::fstream settfile_ = std::fstream(SETTINGS_FILE);

public:
  SettingsParser() = default;
  void FindKey(const std::string &key) {
    // std::filesystem::create_directory("fewfew");
  }

  bool SetValOnKey(Settings key, JsonVal val) {
    for (auto it = settings_.begin(); it != settings_.end(); ++it) {
      if (key == it->inner) {
        it->json_val = val;
        return true;
      }
    }
    return false;
  }

  void FindForeignKey(Settings key){

  }
};

} // namespace s21

#endif // !SETTINGS_PARSER_H_
