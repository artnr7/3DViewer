#ifndef SETTINGS_PARSER_H_
#define SETTINGS_PARSER_H_

#include <iostream>
#include <numeric>
#include <qvariant.h>

#include <filesystem>
#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#define SETTINGS_FILE "ttt.txt"

namespace s21 {

class SettingsParser {
private:
  enum class Settings {
    RotAngleX = 0, // const
    RotAngleY,
    RotAngleZ,

    TransFactorX,
    TransFactorY,
    TransFactorZ,

    ScaleFactorX,
    ScaleFactorY,
    ScaleFactorZ,

    VertexSz,
    VertexStyle,

    VertexClrR,
    VertexClrG,
    VertexClrB,

    EdgeSz,
    EdgeStyle,

    EdgeClrR,
    EdgeClrG,
    EdgeClrB,

    BckgClrR,
    BckgClrG,
    BckgClrB,

    Proj,

    Render,

    Filename,
  };

  using type = uint16_t;
  using val = float;
  using JsonVal = std::variant<val, type, std::string>;
  using foreign_key = const std::string;

  struct Arcana {
    foreign_key key;
    JsonVal json_val;
  };

  std::unordered_map<const Settings, Arcana> settings_{
      {Settings::RotAngleX, {"rotationAngleX", val()}},
      {Settings::RotAngleY, {"rotationAngleY", val()}},
      {Settings::RotAngleZ, {"rotationAngleZ", val()}},

      {Settings::TransFactorX, {"translationFactorX", val()}},
      {Settings::TransFactorY, {"translationFactorY", val()}},
      {Settings::TransFactorZ, {"translationFactorZ", val()}},

      {Settings::ScaleFactorX, {"scaleFactorX", val()}},
      {Settings::ScaleFactorY, {"scaleFactorY", val()}},
      {Settings::ScaleFactorZ, {"scaleFactorZ", val()}},

      {Settings::VertexSz, {"vertexSize", val()}},
      {Settings::VertexStyle, {"vertexStyle", type()}},

      {Settings::VertexClrR, {"vertexClrR", val()}},
      {Settings::VertexClrG, {"vertexClrG", val()}},
      {Settings::VertexClrB, {"vertexClrB", val()}},

      {Settings::EdgeSz, {"edgeSize", val()}},
      {Settings::EdgeStyle, {"edgeStyle", type()}},
      {Settings::EdgeClrR, {"edgeColorR", val()}},
      {Settings::EdgeClrG, {"edgeColorG", val()}},
      {Settings::EdgeClrB, {"edgeColorB", val()}},

      {Settings::BckgClrR, {"backgroundColorR", val()}},
      {Settings::BckgClrG, {"backgroundColorG", val()}},
      {Settings::BckgClrB, {"backgroundColorB", val()}},

      {Settings::Proj, {"projectionType", type()}},
      {Settings::Render, {"renderType", type()}},

      {Settings::Filename, {"filename", std::string()}},
  };

  // std::fstream settfile_ = std::fstream(SETTINGS_FILE);
  std::fstream settfile_;
  using Str = std::string;
  using StrIt = std::string::iterator;
  using CStrIt = std::string::const_iterator;

  // void FindLine(foreign_key key) {
  //   Str str;
  //   while (std::getline(settfile_, str)) {
  //     if (str == key){
  //
  //     }
  //   }
  // }

  void UpdateSetting() {
    std::cout << " greogjergergij" << std::endl;
    Str str;
    if (settfile_.is_open()) {
      std::cout << "==========================" << std::endl;
    } else {
      std::cout << "------------------------------------------------"
                << std::endl;
    }
    for (const auto &[inner, arcana] : settings_) {
      auto [key, secret] = arcana;
      settfile_ << key << "=";
      std::cout << key << "=";
      // std::visit([&](auto &&value) { settfile_ << value; }, secret);
      // auto print_val = [&](const auto &value) { settfile_ << value; };
      // std::visit(print_val, secret);
      settfile_ << "\n";
      std::cout << "\n";
    }
    // std::cout << "=== ДИАГНОСТИКА ===" << std::endl;
    // std::cout << "1. Настроек: " << settings_.size() << std::endl;
    // std::cout << "2. Файл открыт: " << (settfile_.is_open() ? "ДА" : "НЕТ")
    //           << std::endl;
    // std::cout << "3. Ошибок в потоке: " << (settfile_.fail() ? "ДА" : "НЕТ")
    //           << std::endl;
    // std::cout << "4. Размер файла: "
    //           << std::filesystem::file_size(SETTINGS_FILE) << " байт"
    //           << std::endl;
    // std::cout << "5. После close: " <<
    // std::filesystem::file_size(SETTINGS_FILE)
    //           << std::endl;
    settfile_.flush();
    settfile_.close();
  }

  void SetEdgeSz(val edge_sz) {
    auto it = settings_.find(Settings::EdgeSz);
    auto [inner, arcana] = *it;
    arcana.json_val = edge_sz;
  }

public:
  SettingsParser() {
    // settfile_.flush();
    // settfile_.close();

    settfile_.open(SETTINGS_FILE, std::ios::out | std::ios::trunc);
    UpdateSetting();
  }

  // ~SettingsParser() {
  //   settfile_.flush();
  //   settfile_.close();
  // }
};

} // namespace s21

#endif // !SETTINGS_PARSER_H_
