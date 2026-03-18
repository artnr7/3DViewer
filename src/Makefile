NPROC := $(shell expr $$(nproc) / 2)
ifeq ($(shell expr $(NPROC) \< 1), 1)
  NPROC := 1
endif

X11 := QT_QPA_PLATFORM=xcb
PROTOCOL := $(X11)

EXECUTABLE := 3DViewer
BIN_DIR := build/bin

.PHONY: build run test test-% test-verbose-% clang-format-test clang-format-fix valgrind coverage help clean configure

configure:
	@cmake -B build -DENABLE_COVERAGE=ON

build: configure
	@cmake --build build --parallel $(NPROC)

rebuild: clean build

run: build
	mkdir -p logs
	rm -f logs/3dviewer.log
	$(PROTOCOL) ./$(BIN_DIR)/$(EXECUTABLE)

r: run

rr:
	mkdir -p logs
	rm -f logs/3dviewer.log
	$(PROTOCOL) ./$(BIN_DIR)/$(EXECUTABLE)

test: build
	@ctest --test-dir build --parallel $(NPROC) --output-on-failure

test-%: build
	@ctest --test-dir build --parallel $(NPROC) -R ^$*$$ --output-on-failure

test-verbose-all: build
	@ctest --test-dir build --parallel $(NPROC) -VV

test-verbose-%: build
	@ctest --test-dir build --parallel $(NPROC) -V -R ^$*$$

check-clang-format:
	cmake --build build --target check-clang-format

fix-clang-format:
	cmake --build build --target fix-clang-format

valgrind:
	cmake --build build --target valgrind-test

coverage:
	cmake --build build --target coverage

clean:
	rm -rf build

help:
	@echo '=== Available commands ==='
	@echo 'Build:'
	@echo '  make configure          — конфигурация CMake'
	@echo '  make build              — конфигурация и сборка'
	@echo '  make run                — собрать и запустить программу'
	@echo '  make clean              — очистить сборку'
	@echo '  make rebuild            — полная пересборка'
# 	@echo '  make install            — установка в ./install_dir'
	@echo ''
	@echo 'Testing:'
	@echo '  make test                — все тесты'
	@echo '  make test-<name>         — один тест'
	@echo '  make test-verbose-all    — все тесты с подробным выводом'
	@echo '  make test-verbose-<name> — один тест с подробным выводом'
	@echo '  make valgrind            — тесты с valgrind'
	@echo ''
	@echo 'Formatting:'
	@echo '  make check-clang-format  — проверить стиль кода'
	@echo '  make fix-clang-format    — автоисправить стиль'
	@echo '  make check-cmake-format  — проверить стиль CMake'
	@echo '  make fix-cmake-format    — автоисправить стиль CMake'
	@echo ''
	@echo 'Analysis:'
	@echo '  make coverage           — code coverage'
	@echo ''
	@echo 'Note: Executable name is "$(EXECUTABLE)"'

#### TODO: Clear it ####
#config_debug:
#	@/usr/bin/cmake -DCMAKE_BUILD_TYPE:STRING=Debug\
#	-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE\
#	-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc\
#	-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++\
#	--no-warn-unused-cli -S /home/atrnr7/3DViewer/src\
#	-B /home/atrnr7/3DViewer/src/build -G "Unix Makefiles"

# build:
# 	@cmake -B build
# 	@cmake --build build --parallel $(NPROC)


# all:

# app: build
# 	@cmake --build build --target run_3dviewer --parallel $(NPROC)

# log:
# 	@less -R logs/app.log

# gdb:
# 	@cmake --build build --target run_gdb --parallel ${NPROC}
	
# rv: create_folder
# 	@cmake -B build -DCMAKE_BUILD_TYPE=Debug   
# 	@cmake --build build --parallel $(NPROC)
# 	@cmake --build build --target run_3dviewer --parallel $(NPROC)


# # tp:
# # 	@cmake --build build --target run_test_parser --parallel $(NPROC)


# ###--------→ DVI ←--------------------------------------------------------------------###
# # DOXY_DIR := docs/brick_game_v2.0
# # dvi:
# # 	doxygen $(DOXY_DIR)/Doxyfile

# ###--------→ DIST ←--------------------------------------------------------------------###
# # DIST_DIR := dist_dir 
# # BRICKGAME_DIST_ARCH := brick_game-2.0.tar.gz

# # BRICKGAME_DIST_FILES := brick_game gui play Makefile\
# #  CMakeLists.txt cmake ${TEST_DIR} docs

# # dist:
# # 	@mkdir -p $(DIST_DIR)
# # 	@cp -r $(BRICKGAME_DIST_FILES) $(DIST_DIR)
# # 	@tar -czf ${BRICKGAME_DIST_ARCH} $(DIST_DIR)
# # 	@rm -rf $(DIST_DIR)
# # 	@echo "Dist done"

# ###--------→ TEST ←--------------------------------------------------------------------###

	
# ###--------→ REBUILD ←--------------------------------------------------------------------###
# r: 
# 	@cmake -B build -DCMAKE_BUILD_TYPE=Debug   
# 	@cmake --build build --target clean --parallel $(NPROC)    


# ###--------→ CLANG ←---------------------------------------------------------------###
# clang_f:
# 	cmake --build build --target clang_format_fix --parallel $(NPROC) 

# ###--------→ CMAKE ←---------------------------------------------------------------###
# cmake_f: 
# 	@cmake --build build --target cmake_format_fix --parallel $(NPROC) 

# ###--------→ FORMAT ←--------------------------------------------------------------------###
# f: clang_f cmake_f

# ###--------→ CLEAN ←------------------------------------------------------------###
# FILES_TO_CLEAN := build .cache

# clean: 
# 	@rm -rf $(FILES_TO_DEL)
# 	@echo "Clean done"	 

# ###--------→ DELETE ←------------------------------------------------------------###
# FILES_TO_DEL := build install_dir .cache
# del: 
# 	@rm -rf $(FILES_TO_DEL)
# 	@echo "Delete done"	


# # fcl: f clean 
# # 	@echo "Clean and Format done"
