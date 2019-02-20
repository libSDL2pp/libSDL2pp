CXX?=			g++

CXXFLAGS+=		-std=c++11

all: make-ext-test

make-ext-test:
	${CXX} -o make-ext-test ../../examples/sprites.cc ${CXXFLAGS} `pkg-config --cflags --libs sdl2pp`
