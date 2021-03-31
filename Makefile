build:
	g++ voronoi-array-gen.cpp \
	-IC:\Development\SDL2-MinGW-32\include \
	-LC:\Development\SDL2-MinGW-32\lib \
	-w -Wl,-subsystem,windows \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-o voronoi_gen