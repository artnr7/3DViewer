#ifndef SETTINGS_PARSER_H_
#define SETTINGS_PARSER_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <qvariant.h>

#include <filesystem>
#include <fstream>
#include <stack>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#define SETTINGS_FILE "ttt.txt"

namespace s21 {

class SettingsParser {
private:
  using Str = std::string;

  using Key = const Str;

  using Type = uint16_t;
  using Rate = float;
  using Val = std::variant<Rate, Type, std::string>;

  std::map<Key, Val> settings_{
      {"rotationAngleX", Rate()},
      {"rotationAngleY", Rate()},
      {"rotationAngleZ", Rate()},

      {"translationFactorX", Rate()},
      {"translationFactorY", Rate()},
      {"translationFactorZ", Rate()},

      {"scaleFactorX", Rate()},
      {"scaleFactorY", Rate()},
      {"scaleFactorZ", Rate()},

      // Vertex
      {"vertexSize", Rate()},
      {"vertexStyle", Type()},

      {"vertexColorR", Rate()},
      {"vertexColorG", Rate()},
      {"vertexColorB", Rate()},

      // Edge
      {"edgeSize", Rate()},
      {"edgeStyle", Type()},

      {"edgeColorR", Rate()},
      {"edgeColorG", Rate()},
      {"edgeColorB", Rate()},

      // Background
      {"backgroundColorR", Rate()},
      {"backgroundColorG", Rate()},
      {"backgroundColorB", Rate()},

      {"projectionType", Type()},
      {"renderType", Type()},

      {"filename", Str()},
  };

  std::fstream settfile_ = std::fstream(SETTINGS_FILE, std::ios::in);

  void ParseSettings() {
    Str str{};
    Str key_s{};
    Str val_s{};

    while (std::getline(settfile_, str)) {
      size_t eq = str.find('=');
      size_t end = str.size() - 1;

      // std::cout << eq << "  " << end << std::endl;

      Str key_s = str.substr(0, eq);
      Str val_s = str.substr(eq + 1, end);
      // std::cout << key_s << " " << val_s << std::endl;

      auto it = settings_.find(key_s);
      if (it == settings_.end()) {
        continue;
      }

      auto &[key, val] = *it;

      std::visit(
          [&](auto &val) {
            using T = std::decay_t<decltype(val)>;

            if constexpr (std::is_same_v<T, Rate>) {
              val = std::stof(val_s); // float
              // std::cout << val << " ";
            } else if constexpr (std::is_same_v<T, Type>) {
              val = std::stoi(val_s); // uint16_t
              // std::cout << val << " ";
            } else if constexpr (std::is_same_v<T, Str>) {
              val = val_s;
              // std::cout << val << " ";
            }
          },
          val);

      // std::visit([&](auto &&it) { std::cout << it << std::endl; },
      // it->second);
    }
    settfile_.clear();
    settfile_.seekg(0);
    settfile_.close();
  }

  void UpdateSettings() {
    settfile_.open(SETTINGS_FILE, std::ios::out | std::ios::trunc);
    if (!settfile_.is_open()) {
      return;
    }

    for (const auto &[key, val] : settings_) {
      settfile_ << key << "=";
      // std::cout << key << "=";
      std::visit(
          [&](auto &&val) {
            settfile_ << val;
            // std::cout << value;
          },
          val);
      settfile_ << "\n";
      // std::cout << "\n";
    }
    settfile_.flush();
    settfile_.close();
  }

  void Print() {
    std::cout << "\n\nSettings Print\n--------------------------\n";
    for (auto &it : settings_) {
      auto [k, v] = it;
      std::cout << std::left << std::setw(25) << k;
      std::visit([&](auto &&v) { std::cout << std::setw(7) << v; }, v);
      std::cout << "\n";
    }
  }

  void Tmp(Key key, Val val) {
    auto it = settings_.find(key);
    auto [k, v] = *it;
    std::visit([&](auto &&val) { v = val; }, val);
  }

  void SetRotAngles(Rate x, Rate y, Rate z) {
    Tmp("rotationAngleX", x);
    Tmp("rotationAngleY", y);
    Tmp("rotationAngleZ", z);
  }

  void SetTransFactors(Rate x, Rate y, Rate z) {
    Tmp("translationFactorX", x);
    Tmp("translationFactorY", y);
    Tmp("translationFactorZ", z);
  }

  void SetScaleFactors(Rate x, Rate y, Rate z) {
    Tmp("scaleFactorX", x);
    Tmp("scaleFactorY", y);
    Tmp("scaleFactorZ", z);
  }

  // Vertex
  void SetVertexSz(Rate vertex_sz) { Tmp("vertexSize", vertex_sz); }
  void SetVertexStyle(Type vertex_style) { Tmp("vertexStyle", vertex_style); }

  void SetVertexClr(Rate r, Rate g, Rate b) {
    Tmp("vertexColorR", r);
    Tmp("vertexColorG", g);
    Tmp("vertexColorB", b);
  }

  // Edge
  void SetEdgeSz(Rate edge_sz) { Tmp("edgeSize", edge_sz); }
  void SetEdgeStyle(Type edge_style) { Tmp("edgeStyle", edge_style); }

  void SetEdgeClr(Rate r, Rate g, Rate b) {
    Tmp("edgeColorR", r);
    Tmp("edgeColorG", g);
    Tmp("edgeColorB", b);
  }

  void SetBckgClr(Rate r, Rate g, Rate b) {
    Tmp("backgroundColorR", r);
    Tmp("backgroundColorG", g);
    Tmp("backgroundColorB", b);
  }

  void SetProj(Type proj) { Tmp("projectionType", proj); }

  void SetRender(Type render) { Tmp("renderType", render); }

  void SetFilename(const std::string &filename) { Tmp("filename", filename); }

public:
  SettingsParser() {
    ParseSettings();
    Print();
    UpdateSettings();
  }

  ~SettingsParser() {
    // settfile_.flush();
    settfile_.close();
  }
};

} // namespace s21

#endif // !SETTINGS_PARSER_H_
