#ifndef SETTINGS_PARSER_H_
#define SETTINGS_PARSER_H_

#include <cmath>
#include <cstdint>
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

#define SETTINGS_FILE "build/bin/settings.txt"

namespace s21 {

class SettingsParser {
private:
  using Str = std::string;

  using Key = const Str;

  using Type = uint16_t;
  using Rate = float;
  using Color = uint8_t;

  using Val = std::variant<Rate, Type, std::string>;
  using Settings = std::map<Key, Val>;

private:
  Settings settings_{
      {"rotationAngleX", Rate(0.0f)},
      {"rotationAngleY", Rate(0.0f)},
      {"rotationAngleZ", Rate(0.0f)},

      {"translationFactorX", Rate(0.0f)},
      {"translationFactorY", Rate(0.0f)},
      {"translationFactorZ", Rate(0.0f)},

      {"scaleFactor", Rate(1.0f)},

      // Vertex
      {"vertexSize", Rate(10.0f)},
      {"vertexStyle", Type(0)},

      {"vertexColorR", Color(0)},
      {"vertexColorG", Color(49)},
      {"vertexColorB", Color(83)},

      // Edge
      {"edgeSize", Rate(10.0f)},
      {"edgeStyle", Type(0)},

      {"edgeColorR", Color(255)},
      {"edgeColorG", Color(36)},
      {"edgeColorB", Color(0)},

      // Background
      {"backgroundColorR", Color(197)},
      {"backgroundColorG", Color(208)},
      {"backgroundColorB", Color(230)},

      {"projectionType", Type(0)},
      {"renderType", Type(0)},

      {"filename", Str("")},
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

public:
  // Setters
  void Tmp(Key key, Val val) {
    auto it = settings_.find(key);
    auto &[k, v] = *it;
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

  void SetScaleFactors(Rate sc_fct) { Tmp("scaleFactor", sc_fct); }

  // Vertex
  void SetVertexSz(Rate vertex_sz) { Tmp("vertexSize", vertex_sz); }
  void SetVertexStyle(Type vertex_style) { Tmp("vertexStyle", vertex_style); }

  void SetVertexClr(Type r, Type g, Type b) {
    Tmp("vertexColorR", r);
    Tmp("vertexColorG", g);
    Tmp("vertexColorB", b);
  }

  // Edge
  void SetEdgeSz(Rate edge_sz) { Tmp("edgeSize", edge_sz); }
  void SetEdgeStyle(Type edge_style) { Tmp("edgeStyle", edge_style); }

  void SetEdgeClr(Type r, Type g, Type b) {
    Tmp("edgeColorR", r);
    Tmp("edgeColorG", g);
    Tmp("edgeColorB", b);
  }

  void SetBckgClr(Type r, Type g, Type b) {
    Tmp("backgroundColorR", r);
    Tmp("backgroundColorG", g);
    Tmp("backgroundColorB", b);
  }

  void SetProjType(Type proj) { Tmp("projectionType", proj); }

  void SetRenderType(Type render) { Tmp("renderType", render); }

  void SetFilename(const std::string &filename) { Tmp("filename", filename); }

  // Getters
  template <typename Type> Type Tme(Key key) {
    auto it = settings_.find(key);
    if (it == settings_.end()) {
      return Type{};
    }
    auto [k, v] = *it;
    if (auto *f = std::get_if<Type>(&v)) {
      return *f;
    }
    return Type{};
  }

  Rate GetRotAngleX() { return Tme<Rate>("rotationAngleX"); }
  Rate GetRotAngleY() { return Tme<Rate>("rotationAngleY"); }
  Rate GetRotAngleZ() { return Tme<Rate>("rotationAngleZ"); }

  Rate GetTransFactorX() { return Tme<Rate>("translationFactorX"); }
  Rate GetTransFactorY() { return Tme<Rate>("translationFactorY"); }
  Rate GetTransFactorZ() { return Tme<Rate>("translationFactorZ"); }

  Rate GetScaleFactor() { return Tme<Rate>("scaleFactor"); }

  Rate GetVertexSz() { return Tme<Rate>("vertexSize"); }
  Type GetVertexStyle() { return Tme<Type>("vertexStyle"); }

  Rate GetVertexClrR() { return Tme<Type>("vertexColorR"); }
  Rate GetVertexClrG() { return Tme<Type>("vertexColorG"); }
  Rate GetVertexClrB() { return Tme<Type>("vertexColorB"); }

  Rate GetEdgeSz() { return Tme<Rate>("edgeSize"); }
  Type GetEdgeStyle() { return Tme<Type>("edgeStyle"); }

  Rate GetEdgeClrR() { return Tme<Type>("edgeColorR"); }
  Rate GetEdgeClrG() { return Tme<Type>("edgeColorG"); }
  Rate GetEdgeClrB() { return Tme<Type>("edgeColorB"); }

  Rate GetBckgClrR() { return Tme<Type>("backgroundColorR"); }
  Rate GetBckgClrG() { return Tme<Type>("backgroundColorG"); }
  Rate GetBckgClrB() { return Tme<Type>("backgroundColorB"); }

  Type GetProjType() { return Tme<Type>("projectionType"); }
  Type GetRenderType() { return Tme<Type>("renderType"); }

  Str GetFilename() { return Tme<Str>("filename"); }

  Settings &GetSettings() { return settings_; }

  // Constructors
  SettingsParser() {
    ParseSettings();
    // Print();
    // UpdateSettings();
  }

  ~SettingsParser() {
    // settfile_.flush();
    settfile_.close();
  }
};

} // namespace s21

#endif // !SETTINGS_PARSER_H_
