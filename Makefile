LDFLAGS += `pkg-config --libs sdl2 SDL2_image`
compile:
	clang++ -o bin/game src/**.cpp $(LDFLAGS) -std=c++14 -Og -g
run:
	bin/game
