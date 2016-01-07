all: sfml-mandelbrot

sfml-mandelbrot: main.o
	g++ -std=c++11 main.o -o sfml-mandelbrot -lsfml-graphics -lsfml-window -lsfml-system -fopenmp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -fopenmp

clean:
	rm *o sfml-mandelbrot
