CXX?=			g++

CXXFLAGS+=		-std=c++11

all: make-ext-test

make-ext-test:
	@echo "SDL2PP_CFLAGS=${SDL2PP_CFLAGS}"
	@echo "SDL2PP_LIBS=${SDL2PP_LIBS}"
	${CXX} -o make-ext-test ../../examples/sprites.cc ${CXXFLAGS} `pkg-config --cflags --libs sdl2pp`
