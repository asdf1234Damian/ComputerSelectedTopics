#include <SFML/Graphics.hpp>
#include <vector>

const int size=1000;

class Automata{
public:
  Automata();
  void run();
private:
  sf::RenderWindow m_window;
  std::vector<sf::Vertex> m_pixels;
  void pollEvent();
  void setCell(int x, int y, sf::Uint8 c);
};
