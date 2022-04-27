CXX?=			g++

CXXFLAGS+=		-std=c++17

SDL2PP_CFLAGS=	`pkg-config --cflags sdl2pp`
SDL2PP_LIBS=	`pkg-config --libs sdl2pp`

all: make-ext-test

make-ext-test:
	@echo "SDL2PP_CFLAGS=${SDL2PP_CFLAGS}"
	@echo "SDL2PP_LIBS=${SDL2PP_LIBS}"
	${CXX} ${CXXFLAGS} ../../examples/sprites.cc -o make-ext-test ${SDL2PP_CFLAGS} ${SDL2PP_LIBS}
