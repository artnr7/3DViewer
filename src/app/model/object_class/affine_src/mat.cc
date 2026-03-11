#include "../object_class.h"
#include <array>
#include <glm/ext/matrix_transform.hpp>

namespace s21 {

void Object::Affine::SetTranslate(vec4 vec) { mat_trans_.TranslateOn(vec); }

} // namespace s21
