#include "object_class.h"

namespace s21 {
void Object::Affine::Translate(const short shift, float arg) {
  // TODO(sundaeka): проверка на размера массива, должен быть минимум 3
  for (auto it = obj_.glvertices_.begin() + shift; it != obj_.glvertices_.end();
       it += 3) {
    it += arg;
  }
}

void Object::Affine::TranslateX(float x) { Translate(0, x); }
void Object::Affine::TranslateY(float y) { Translate(1, y); }
void Object::Affine::TranslateZ(float z) { Translate(2, z); }

} // namespace s21
