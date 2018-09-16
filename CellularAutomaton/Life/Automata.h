#include <SFML/Graphics.hpp>
#include <vector>
class Automata{
public:
  unsigned int size;
  Automata(unsigned int size);
  bool running=false;
  void run();
  void randomStart();
  void update();
private:
  int ls=2,us=3,lb=3,ub=3;
  sf::RenderWindow grid;
  std::vector<sf::Vertex> cells;
  std::vector<sf::Vertex> cellsNext;
  void pollEvent();
  short int getValue(float x, float y);
  short int neighSum(float x, float y);
  bool rule(float x, float y);
  size_t getIndex(float x, float y);
  void setCell(float x, float y);

  //void update();
};
