#ifndef SETTINGS_PARSER_H_
#define SETTINGS_PARSER_H_

#include <qvariant.h>

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

#include "../../api/primitives.h"

#define SETTINGS_FILE "build/bin/settings.txt"

namespace s21 {

class SettingsParser {
 private:
  using Key = const Str;

  using Enum = uint16_t;
  using Rate = float;

  using Val = std::variant<Angles, Rates, Color, Rate, Enum, Str>;
  using Settings = std::map<Key, Val>;

  Settings settings_{
      // default
      {"translationRates", Rates{.x = 0.0f, .y = 0.0f, .z = 0.0f}},
      {"rotationAngles", Angles{.x = 0.0f, .y = 0.0f, .z = 0.0f}},

      {"scaleRate", Rate(1.0f)},

      // Vertex
      {"vertexSize", Rate(10.0f)},
      {"vertexStyle", Enum(0)},

      {"vertexColor", Color{.x = 0, .y = 49, .z = 83}},  // default

      // Edge
      {"edgeSize", Rate(10.0f)},
      {"edgeStyle", Enum(0)},

      {"edgeColor", Color{.x = 255, .y = 36, .z = 0}},  // default

      // Background
      {"backgroundColor", Color{.x = 197, .y = 208, .z = 230}},  // default

      {"projectionType", Enum(0)},
      {"renderType", Enum(0)},

      {"filename", Str("")},
  };

  std::fstream settfile_ = std::fstream(SETTINGS_FILE);

  inline static bool IsStrNpos(size_t pos) { return pos == Str::npos; }

  void ParseSettings() {
    settfile_.open(SETTINGS_FILE, std::ios::in);
    // а почему без этих 2 строк не работает???????
    settfile_.clear();
    settfile_.seekg(0);
    if (!settfile_.is_open()) {
      return;
    }

    Str str, key_s{};

    size_t eq{}, end{}, f_spc{}, s_spc{};

    while (std::getline(settfile_, str)) {
      // std::cout << "\n\nParseSettings\n\n" << std::endl;
      eq = str.find('=');
      end = str.size() - 1;
      f_spc = str.find(' ');
      s_spc = str.rfind(' ');

      // Проверки на Npos
      key_s = str.substr(0, eq);

      auto it = settings_.find(key_s);
      if (it == settings_.end()) {
        continue;
      }

      // std::cout << eq << "  " << end << " " << f_spc << " " << s_spc
      //           << std::endl;
      if (IsStrNpos(f_spc) && IsStrNpos(s_spc)) {
        ParseSimple(str, it, eq, end);
      }
      if (!IsStrNpos(f_spc) && !IsStrNpos(s_spc)) {
        ParseTriple(str, it, eq, f_spc, s_spc, end);
      }
    }
    settfile_.clear();
    settfile_.seekg(0);
    settfile_.close();
  }

  void ParseSimple(const Str& str, const Settings::iterator& it,
                   const size_t eq, const size_t end) {
    std::cout << "ParseSimple" << std::endl;
    Str val = str.substr(eq + 1, end);
    // std::cout << key_s << " " << val_s << std::endl;

    std::cout << eq << "  " << end << std::endl;
    auto& [k, v] = *it;

    std::visit(
        [&](auto& v) {
          using T = std::decay_t<decltype(v)>;

          if constexpr (std::is_same_v<T, Rate>) {
            v = std::stof(val);  // float
            // std::cout << val << " ";
          } else if constexpr (std::is_same_v<T, Enum>) {
            v = std::stoi(val);  // uint16_t
            // std::cout << val << " ";
          } else if constexpr (std::is_same_v<T, Str>) {
            v = val;
            // std::cout << val << " ";
          }
        },
        v);

    // std::visit([&](auto &&it) { std::cout << it << std::endl; },
    // it->second);
  }
  void ParseTriple(const Str& str, const Settings::iterator& it,
                   const size_t eq, const size_t f_spc, const size_t s_spc,
                   const size_t end) {
    std::cout << "ParseTriple" << std::endl;
    Str val_1 = str.substr(eq + 1, f_spc);
    Str val_2 = str.substr(f_spc + 1, s_spc);
    Str val_3 = str.substr(s_spc + 1, end);
    // std::cout << key_s << " " << val_s << std::endl;
    std::cout << eq << "  " << end << " " << f_spc << " " << s_spc << std::endl;

    auto& [k, v] = *it;

    std::visit(
        [&](auto& v) {
          using T = std::decay_t<decltype(v)>;

          if constexpr (std::is_same_v<T, Angles> || std::is_same_v<T, Rates> ||
                        std::is_same_v<T, Color>) {
            v.x = std::stof(val_1);
            v.y = std::stof(val_2);
            v.z = std::stof(val_3);
            // std::cout << val << " ";
          }
        },
        v);

    // std::visit([&](auto &&it) { std::cout << it << std::endl; },
    // it->second);
  }

  void UpdateSettings() {
    // std::cout << "fewfewfwefwe" << std::endl;
    settfile_.open(SETTINGS_FILE, std::ios::out | std::ios::trunc);
    if (!settfile_.is_open()) {
      return;
    }

    for (const auto& [k, v] : settings_) {
      settfile_ << k << "=";
      std::cout << k << "=";
      std::visit(
          [&](auto&& v) {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T, Angles> ||
                          std::is_same_v<T, Rates> ||
                          std::is_same_v<T, Color>) {
              settfile_ << static_cast<float>(v.x) << " "
                        << static_cast<float>(v.y) << " "
                        << static_cast<float>(v.z);

              std::cout << static_cast<float>(v.x) << " "
                        << static_cast<float>(v.y) << " "
                        << static_cast<float>(v.z);
            } else if constexpr (std::is_same_v<T, Rate> ||
                                 std::is_same_v<T, Enum> ||
                                 std::is_same_v<T, Str>) {
              settfile_ << v;
              std::cout << v;
            }
          },
          v);
      settfile_ << "\n";
      std::cout << "\n";
    }
    settfile_.flush();
    settfile_.close();
  }

  void Print() {
    std::cout << "\n\nSettings Print\n--------------------------\n";
    for (const auto& [k, v] : settings_) {
      std::cout << std::left << std::setw(25) << k;
      std::visit(
          [&](auto&& v) {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T, Angles> ||
                          std::is_same_v<T, Rates> ||
                          std::is_same_v<T, Color>) {
              std::cout << static_cast<float>(v.x) << " "
                        << static_cast<float>(v.y) << " "
                        << static_cast<float>(v.z);
            } else if constexpr (std::is_same_v<T, Rate> ||
                                 std::is_same_v<T, Enum> ||
                                 std::is_same_v<T, Str>) {
              std::cout << v;
            }
          },
          v);
      std::cout << "\n";
    }
  }

 public:
  // Setters
  void Set(Key key, Val val) {
    auto it = settings_.find(key);
    auto& [k, v] = *it;

    std::visit(
        [&](auto&& v) {
          using T = std::decay_t<decltype(v)>;

          if (auto* f = std::get_if<T>(&val)) {
            v = *f;
          }
        },
        v);
  }

  // Affine
  void SetRotAngles(Angles angles) { Set("rotationAngles", angles); }
  void SetTransRates(Rates rates) { Set("translationRates", rates); }
  void SetScaleRate(Rate sc_rate) { Set("scaleRate", sc_rate); }

  // Vertex
  void SetVertSz(Rate vert_sz) { Set("vertexSize", vert_sz); }
  void SetVertStyle(Enum vert_style) { Set("vertexStyle", vert_style); }
  void SetVertClr(Color clr) { Set("vertexColor", clr); }

  // Edge
  void SetEdgeSz(Rate edge_sz) { Set("edgeSize", edge_sz); }
  void SetEdgeStyle(Enum edge_style) { Set("edgeStyle", edge_style); }
  void SetEdgeClr(Color clr) { Set("edgeColor", clr); }

  // Misc
  void SetBckgClr(Color clr) { Set("backgroundColor", clr); }
  void SetProjType(Enum proj) { Set("projectionType", proj); }
  void SetRenderType(Enum render) { Set("renderType", render); }
  void SetFilename(Str& filename) { Set("filename", filename); }

  // Getters
  template <typename Type>
  const Type& Get(Key key) {
    auto it = settings_.find(key);
    if (it == settings_.end()) {
      throw std::runtime_error("wrong setting file");
    }

    auto [k, v] = *it;
    auto* f = std::get_if<Type>(&v);
    if (f == nullptr) {
      throw std::runtime_error("wrong setting file");
    }

    return *f;
  }

  // Affine
  const Angles& GetRotAngles() { return Get<Angles>("rotationAngles"); }
  const Rates& GetTransRates() { return Get<Rates>("translationFactorX"); }
  const Rate& GetScaleRate() { return Get<Rate>("scaleRate"); }

  // Vertex
  const Rate& GetVertSz() { return Get<Rate>("vertexSize"); }
  const Enum& GetVertStyle() { return Get<Enum>("vertexStyle"); }
  const Color& GetVertClr() { return Get<Color>("vertexColor"); }

  // Edge
  const Rate& GetEdgeSz() { return Get<Rate>("edgeSize"); }
  const Enum& GetEdgeStyle() { return Get<Enum>("edgeStyle"); }
  const Color& GetEdgeClr() { return Get<Color>("edgeColor"); }

  // Misc
  const Color& GetBckgClr() { return Get<Color>("backgroundColor"); }
  const Enum& GetProjType() { return Get<Enum>("projectionType"); }
  const Enum& GetRenderType() { return Get<Enum>("renderType"); }
  const Str& GetFilename() { return Get<Str>("filename"); }

  // const Settings &GetSettings() { return settings_; }

  // Constructors
  SettingsParser() {
    ParseSettings();
    // Print();
    // UpdateSettings();
  }

  ~SettingsParser() {
    // settfile_.flush();
    UpdateSettings();
    settfile_.close();
  }
};

}  // namespace s21

#endif  // !SETTINGS_PARSER_H_
