all: main


USE_QT = 6


ifeq ($(USE_QT), 6)
	QT6_CXXFLAGS = -I/usr/include/x86_64-linux-gnu/qt6
	QT_CXXFLAGS = $(QT6_CXXFLAGS)
	QT6_LDFLAGS = -lQt6Core -lQt6Gui -lQt6Widgets -lQt6OpenGL -lQt6OpenGLWidgets
	QT_LDFLAGS = $(QT6_LDFLAGS)
else
	QT5_CXXFLAGS = -I/usr/include/x86_64-linux-gnu/qt5
	QT_CXXFLAGS = $(QT5_CXXFLAGS)
	QT5_LDFLAGS = -lQt5Core -lQt5Gui -lQt5Widgets -lQt5OpenGL
	QT_LDFLAGS = $(QT5_LDFLAGS)
endif

CXXFLAGS += $(QT_CXXFLAGS)

# Qt::Widgets Qt::OpenGL Qt::Gui Qt::OpenGLWidgets Qt::Core
LDFLAGS += -L/usr/lib/x86_64-linux-gnu/ $(QT_LDFLAGS) -lGL -lGLU

main: main.cpp TriangleWidget.cpp TriangleWidget.h
	c++ -Wall -O0 $(CXXFLAGS) -fPIC -o main main.cpp TriangleWidget.cpp $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f main