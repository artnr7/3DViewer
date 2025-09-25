NPROC := $(shell expr $$(nproc) / 2)
ifeq ($(shell expr $(NPROC) \< 1), 1)
  NPROC := 1
endif

.PHONY: all config_debug app

config_debug:
	@/usr/bin/cmake -DCMAKE_BUILD_TYPE:STRING=Debug\
	-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE\
	-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc\
	-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++\
	--no-warn-unused-cli -S /home/atrnr7/3DViewer/src\
	-B /home/atrnr7/3DViewer/src/build -G "Unix Makefiles"

all: 
	@cmake --build build --parallel $(NPROC)

app:	
	@cmake --build build --target run_3dviewer --parallel $(NPROC)
	
rv:
	@cmake -B build -DCMAKE_BUILD_TYPE=Debug   
	@cmake --build build --parallel $(NPROC)
	@cmake --build build --target run_3dviewer --parallel $(NPROC)
	

# tp:
# 	@cmake --build build --target run_test_parser --parallel $(NPROC)


###--------→ DVI ←--------------------------------------------------------------------###
# DOXY_DIR := docs/brick_game_v2.0
# dvi:
# 	doxygen $(DOXY_DIR)/Doxyfile

###--------→ DIST ←--------------------------------------------------------------------###
# DIST_DIR := dist_dir 
# BRICKGAME_DIST_ARCH := brick_game-2.0.tar.gz

# BRICKGAME_DIST_FILES := brick_game gui play Makefile\
#  CMakeLists.txt cmake ${TEST_DIR} docs

# dist:
# 	@mkdir -p $(DIST_DIR)
# 	@cp -r $(BRICKGAME_DIST_FILES) $(DIST_DIR)
# 	@tar -czf ${BRICKGAME_DIST_ARCH} $(DIST_DIR)
# 	@rm -rf $(DIST_DIR)
# 	@echo "Dist done"

###--------→ TEST ←--------------------------------------------------------------------###

	
###--------→ REBUILD ←--------------------------------------------------------------------###
r: 
	@cmake -B build -DCMAKE_BUILD_TYPE=Debug   
	@cmake --build build --target clean --parallel $(NPROC)    


###--------→ CLANG ←---------------------------------------------------------------###
clang_f:
	cmake --build build --target clang_format_fix --parallel $(NPROC) 

###--------→ CMAKE ←---------------------------------------------------------------###
cmake_f: 
	@cmake --build build --target cmake_format_fix --parallel $(NPROC) 

###--------→ FORMAT ←--------------------------------------------------------------------###
f: clang_f cmake_f

###--------→ CLEAN ←------------------------------------------------------------###
FILES_TO_CLEAN := build .cache

clean: 
	@rm -rf $(FILES_TO_DEL)
	@echo "Clean done"	 

###--------→ DELETE ←------------------------------------------------------------###
FILES_TO_DEL := build install_dir .cache
del: 
	@rm -rf $(FILES_TO_DEL)
	@echo "Delete done"	


# fcl: f clean 
# 	@echo "Clean and Format done"