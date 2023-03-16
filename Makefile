SOURCE = main.cpp
all:
	g++ -Isrc/include -Lsrc/lib -o main $(SOURCE) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

