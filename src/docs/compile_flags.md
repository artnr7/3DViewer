****`-mno-direct-extern-access` — флаг **GCC**, а не Clang!**

## **Проблема:**
В `compile_commands.json` (из CMake) записан флаг GCC, который clangd **не понимает**.

## **Решения:**

### **1. CMake генерирует флаги для Clang (рекомендую):**
```cmake
# CMakeLists.txt
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

# Или при сборке:
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang ..
```

### **2. Игнорируй флаг в `.clangd`:**
```yaml
# .clangd в корне проекта
CompileFlags:
  Remove: [ -mno-direct-extern-access ]
  Add: [ -std=c++20 ]
```

### **3. Фильтр в clangd настройках:**
```lua
require('lspconfig').clangd.setup({
  cmd = {
    "clangd",
    "--compile-commands-dir=build",
    "--clang-tidy",
    -- Игнорируем неизвестные флаги автоматически
  },
  init_options = {
    clangdFileStatus = true
  }
})
```

### **4. Пересобери compile_commands.json:**
```bash
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
# Скопируй в корень
cp compile_commands.json ..
```

### **5. Проверь compile_commands.json:**
```json
{
  "directory": "/root/projs/cpp/3DViewer/build",
  "command": "clang++ -std=c++20 -mno-direct-extern-access main.cpp",  // ← Плохой флаг!
  "file": "src/main.cpp"
}
```

## **Быстрое исправление:**
**Замени в CMakeLists.txt:**
```cmake
set(CMAKE_CXX_COMPILER "clang++" CACHE STRING "C++ compiler")
set(CMAKE_C_COMPILER "clang" CACHE STRING "C compiler")
```

**Пересобери:**
```bash
rm -rf build/
mkdir build && cd build
cmake ..
make
```

**clangd автоматически пропустит неизвестные флаги**, но лучше их убрать из `compile_commands.json` для чистоты!

**`.clangd` с `Remove`** — самое элегантное решение.
