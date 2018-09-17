#include <SFML/Graphics.hpp>
#include <vector>
class Automata{
public:
  unsigned int size,p;
  Automata(unsigned int,short int );
  sf::Color alive= sf::Color(170, 255,253);
  sf::Color dead= sf::Color(0,0,0);
  int zoom=1;
  bool running=false;
  void run();
  void randomStart();
  void update();
  /*void loadFile();
  void writeToFile();*/
private:
  int ls=2,us=3,lb=3,ub=3;
  sf::RenderWindow grid;
  sf::View view;
  std::vector<sf::Vertex> cells;
  std::vector<sf::Vertex> cellsNext;
  void pollEvent();
  short int getValue(float, float);
  short int neighSum(float, float );
  bool rule(float, float);
  size_t getIndex(float , float );
  void setCell(float , float );

  //void update();
};
