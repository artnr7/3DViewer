#ifndef ENUM_UTILS
#define ENUM_UTILS

#include <string_view>

namespace s21 {

template <auto EnumValue>
constexpr auto GetEnumName() {
#if defined(__GNUC__)
  constexpr std::string_view separator = "::";
  constexpr std::string_view str_end = "]";
  constexpr std::string_view pretty_function = __PRETTY_FUNCTION__;
  constexpr size_t start =
      pretty_function.rfind(separator) + separator.length();
  constexpr size_t end = pretty_function.rfind(str_end);
  constexpr std::string_view name = pretty_function.substr(start, end - start);

  return name;
#else
  return "Unsupported compiler";
#endif
}

}  // namespace s21

#endif  // ENUM_UTILS
