all: sfml-mandelbrot

sfml-mandelbrot: main.o
	g++ main.o -o sfml-mandelbrot -lsfml-graphics -lsfml-window -lsfml-system -fopenmp

main.o: main.cpp
	g++ -c main.cpp -fopenmp

clean:
	rm *o sfml-mandelbrot
