<center>

# Документация по CMake

</center>

## Форматирование CMake файлов

Файл: `CMakeFormat.cmake`

**Функции:**

<details>
<summary> register_format_cmake_file() </summary>

Макрос без параметров. Регистрирует **текущий** CMakeLists.txt для форматирования целью fix-cmake-format.
Где вызывать: В **каждом** CMakeLists.txt файле
</details>

<details>
<summary> create_cmake_format_target() </summary>

Функция без параметров. Создает цели fix-cmake-format и check-cmake-format для форматирования всех зарегистрированных CMake файлов.
Где вызывать: Только один раз в главном CMakeLists.txt.
</details>

---

## Форматирование C++ кода

Файл: `ClangFormat.cmake`

**Функции:**

<details>
<summary> register_format_sources(files...) </summary>

Макрос с переменным числом аргументов. Регистрирует C++ исходные файлы для форматирования clang-format. Файлы указываются относительно текущей исходной директории.
Где вызывать: В поддиректориях, содержащих C++ исходники.
Параметры: Список файлов через пробел.

Пример:

```cmake
set(SOURCES
  main.cс
  utils.cс
  include/myheader.h
  src/implementation.cс)

register_format_sources(${SOURCES})
```
</details>

<details>
<summary> create_clang_format_target() </summary>

Функция без параметров. Создает цели `fix-clang-format` и `check-clang-format` для форматирования всех зарегистрированных C++ файлов.
Где вызывать: **Только один раз** в **главном** CMakeLists.txt.

</details>

---
## Покрытие кода

Файл: `Coverage.cmake`

**Функции:**

<details>
<summary> add_coverage_version(lib_name) </summary>

Функция с одним параметром. Создает специальную coverage-версию библиотеки (с суффиксом `_coverage`) с флагами компиляции для анализа покрытия.
Где вызывать: Для каждой библиотеки, которую нужно анализировать в coverage-отчетах.

Параметры:

- `lib_name` - имя существующей библиотеки

Пример:

```cmake
add_library(math STATIC ...)
add_coverage_version(math)  # Создает библиотеку math_coverage
```

</details>

<details>
<summary> target_add_coverage(target_name) </summary>

Функция с одним параметром. Добавляет флаги компиляции и линковки для coverage к указанному таргету (исполняемому файлу или тестам).
Где вызывать: Для тестовых и исполняемых файлов, участвующих в coverage-анализе.

Параметры:
- `target_name` - имя таргета

Пример:
```cmake
add_executable(my_tests ...)
target_add_coverage(my_tests)
```

</details>

<details>
<summary> target_link_libraries_with_coverage(test_target libs...) </summary>

Функция с переменным числом аргументов. Связывает тестовый таргет с библиотеками, автоматически выбирая их coverage-версии если включен режим coverage.
Где вызывать: Для линковки тестов с библиотеками при включенном coverage.

Параметры:

1. `test_target` - имя тестового таргета
2. `libs...` - список библиотек для линковки

Пример:

```cmake
target_link_libraries_with_coverage(my_tests math utils)
# линкует my_tests с библиотекам math_coverage и utils_coverage (если включен флаг ENAMLE_COVERAGE)
```

</details>

<details>
<summary> register_coverage_tests(tests...) </summary>

Макрос с переменным числом аргументов. Регистрирует тестовые таргеты для включения в отчет coverage.
Где вызывать: Для каждого тестового таргета, который должен учитываться в coverage-отчете.

Параметры: 

1. `tests...` - cписок имен тестовых таргетов

Пример:

```cmake
register_coverage_tests(math_tests utils_tests)
```

</details>

<details>
<summary> create_coverage_target() </summary>

Функция без параметров. Создает цель `coverage` для генерации HTML-отчета по покрытию кода.
Где вызывать: **Только один раз** в **главном** CMakeLists.txt.

</details>

## Функции линковки

Файл: `TargetLinkFunctions.cmake`

**Функции:**

<details>
<summary> target_link_gtest(target_name) </summary>

Функция с одним параметром. Связывает таргет с библиотеками Google Test (gtest и gtest_main).
Где вызывать: Для каждого тестового таргета, использующего Google Test.

Параметры:

- `target_name` - имя тестового таргета

Пример:

```cmake
target_link_gtest(my_unit_tests)
```

</details>

<details>
<summary> target_link_qt(target_name) </summary>

Функция с одним параметром. Связывает Qt-приложение с необходимыми компонентами Qt6.
Где вызывать: Для каждой библиотеки требущей линковки с Qt6.

Параметры:

- `target_name` - имя таргета с Qt зависимостью

Пример:

```cmake
target_link_qt(my_qt_lib)
```

</details>

---

## Порядок работы с CMake файлами

1. При добавлении нового модуля создается новый `CMakeLists.txt` в этой директории
2. В начале каждого `CMakeLists.txt` вызывается `register_format_cmake_file()` для регистрации файла
3. Если модуль содержит C++ исходники, они регистрируются через `register_format_sources()`
4. Если формируется библиотека и в дальнейшем она будет использована в тестах и отчёте, то нужно добавить coverage-версию через `add_coverage_version()`
5. Если библиотека линкуется с `qt`, то использовать `target_link_qt()`
6. Для тестов используются специальные функции линковки:
  `target_link_gtest()` для Google Test
  `target_link_libraries_with_coverage()` для линковки с библиотеками
  `register_coverage_tests()` для регистрации в coverage-отчете
7. В корневом CMakeLists.txt (в конце файла) вызываются финальные функции:
  `create_clang_format_target()`
  `create_cmake_format_target()`
  `create_coverage_target()`

---

## Работа с зависимостями

**В С++ файлах не указываются относительные пути к заголовочным файлам!!!**
Библиотека, к которой мы линкуемся, определяет свои публичные заголовки сама. Это осуществляется через добавление заголовочных файлов функцией `target_include_directories()`.

Пример:

```cmake
# math/CMakeLists.txt
add_library(math STATIC matrix.cc include/matrix.h)

# Указываем, где лежат публичные заголовки
target_include_directories(math
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Структура каталогов:
# math/
# ├── include/       ← публичные заголовки
# │   └── matrix.h
# ├── matrix.c
# └── CMakeLists.txt
```

В дальнейшем нам остается только заинклюдить заголовочный файл...

```cpp
// app.cc

#include "matrix.h"

// какой-то код
```

... и прилинковаться к созданной раннее библиотеке:

```cmake
# app/CMakeLists.txt
add_executable(app app.cc)

# Все заголовки math станут доступны автоматически
target_link_libraries(app PRIVATE math)
```
