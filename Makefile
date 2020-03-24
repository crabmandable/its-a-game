DEBUG ?= false

CXX := g++
CXXDEFINES += -DDEBUG=$(DEBUG)
MKDIR := mkdir -p
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_image tinyxml2`
CXXFLAGS += -Wall -Werror -Wextra -pedantic -std=c++14 -g $(CXXDEFINES)
LDFLAGS += `pkg-config --libs sdl2 SDL2_image tinyxml2`
LDFLAGS += -lm
PROG := bin/game
OBJS := $(patsubst src/%.cpp,obj/%.o, $(wildcard src/*.cpp))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: build

build: $(PROG)

-include $(DEPS)

clean:
	rm -rf $(PROG) obj/*

$(PROG): $(OBJS)
	@$(MKDIR) $(dir $@)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

obj/%.o : src/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $< $(CXXFLAGS) -c -MD -o $@


