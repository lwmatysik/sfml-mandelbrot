SYS := $(shell gcc -dumpmachine)

all: sfml-mandelbrot

clean: rm *o sfml-mandelbrot

ifneq (, $(findstring linux, $(SYS)))
sfml-mandelbrot: main.o
	g++ -std=c++11 main.o -o sfml-mandelbrot -lsfml-graphics -lsfml-window -lsfml-system -fopenmp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -fopenmp
endif

ifneq (, $(findstring darwin, $(SYS)))
sfml-mandelbrot: main.o
	g++ -std=c++11 main.o -o sfml-mandelbrot -lsfml-graphics -lsfml-window -lsfml-system -I/usr/local/include -L/usr/local/lib

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -I/usr/local/include
endif
