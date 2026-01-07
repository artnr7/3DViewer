include_guard()

# Find QT
find_package(Qt6 REQUIRED COMPONENTS Core Widgets OpenGL OpenGLWidgets Gui)

# Find GTest
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Find Lcov and GenHtml
find_program(LCOV lcov)
find_program(GENHTML genhtml)

# Find Clang Format
find_program(CLANG_FORMAT "clang-format")

# Find CMake Format
find_program(CMAKE_FORMAT cmake-format)
