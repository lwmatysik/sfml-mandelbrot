#include <SFML/Graphics.hpp>
#include <complex>
#include <sstream>

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;
const int MAX_ITER = 100;

const uint8_t AMOUNT_RED = 33;
const uint8_t AMOUNT_GREEN = 78;
const uint8_t AMOUNT_BLUE = 220;
const uint8_t SHIFT = 0b00000111;

int main() {

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Fractal Example");
  sf::Font font;
  sf::Text text;
  sf::Vertex vertex;
  sf::VertexArray vertexArray(sf::Points, WINDOW_WIDTH * WINDOW_HEIGHT);
  
  if (!font.loadFromFile("res/Munro.ttf")) {
    return 1;
  }
  
  window.setFramerateLimit(60);
  window.clear(sf::Color::Black);
  window.display();
  
  long double pixelReal, pixelImaginary;
  std::complex<long double> tempZ, z;
  std::complex<long double> c;

#pragma omp for ordered schedule(dynamic) collapse(2)
  for (int x = 0; x < WINDOW_WIDTH; x++) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {

      pixelReal = 1.5 * (x - (WINDOW_WIDTH / 2)) / (0.5 * WINDOW_WIDTH);
      pixelImaginary = (y - (WINDOW_HEIGHT / 2)) / (0.5 * WINDOW_HEIGHT);
      z = std::complex<long double>(0, 0);
      c = std::complex<long double>(pixelReal, pixelImaginary);
      
      int i;

#pragma omp ordered
      for (i = 0; i < MAX_ITER; i++) {
	tempZ = z;
	z = tempZ * tempZ + c;
	if ((z.real() * z.real() + z.imag() * z.imag()) > 4) {
	  break;
	}
      }

      int magnitude = i / 8;
      
      vertex.position = sf::Vector2f(x, y);

      if (i == MAX_ITER) {
	vertex.color = sf::Color::Black;
      } else {
	vertex.color = sf::Color(AMOUNT_RED | (SHIFT << magnitude),
				 AMOUNT_GREEN | (SHIFT << magnitude),
				 AMOUNT_BLUE | (SHIFT << magnitude),
				 255);
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

    window.clear(sf::Color::Black);
    text.setString("Max Iteration = " + std::to_string(MAX_ITER));
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);

    window.draw(vertexArray);
    window.draw(text);
    window.display();
    
  }
    
  return 0;
}
