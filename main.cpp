#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;
const int MAX_ITER = 100;

int main() {

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Fractal Example");
  sf::Font font;
  sf::Text text;
  sf::Vertex vertex;
  sf::VertexArray vertexArray(sf::Points, WINDOW_WIDTH * WINDOW_HEIGHT);
  
  if (!font.loadFromFile("res/Munro.ttf")) {
    return 1;
  }
  
  long double pixelReal, pixelImaginary;
  std::complex<long double> oldZ, newZ;
  std::complex<long double> c;

  #pragma omp for ordered schedule(dynamic) collapse(2)
  for (int x = 0; x < WINDOW_WIDTH; x++) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {

      pixelReal = 1.5 * (x - (WINDOW_WIDTH / 2)) / (0.5 * WINDOW_WIDTH);
      pixelImaginary = (y - (WINDOW_HEIGHT / 2)) / (0.5 * WINDOW_HEIGHT);
      newZ = std::complex<long double>(0, 0);
      c = std::complex<long double>(pixelReal, pixelImaginary);

      int i;

      #pragma omp ordered
      for (i = 0; i < MAX_ITER; i++) {
	oldZ = newZ;
	newZ = oldZ * oldZ + c;
	if ((newZ.real() * newZ.real() + newZ.imag() * newZ.imag()) > 4) {
	  break;
	}
      }
	
      vertex.position = sf::Vector2f(x, y);

      if (i == MAX_ITER) {
	vertex.color = sf::Color::Green;
      } else {
	vertex.color = sf::Color::Black;
      }
	
      vertexArray.append(vertex);
	
    }

  }
 
    while (window.isOpen()) {

    sf::Event event;
    
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
	window.close();
      }

    }

    text.setFont(font);
    text.setString("Here are your mandelbrots bro.");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Red);

    window.draw(vertexArray);
    window.draw(text);
    window.display();
    
  }

    return 0;
}
