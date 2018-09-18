#include <SFML/Graphics.hpp>
#include <vector>
class Automata{
public:
  unsigned int size,p;
  Automata(unsigned int,short int );
  sf::Color alive= sf::Color(250, 250,250);
  sf::Color dead= sf::Color(0,0,0);
  int ls=2,us=3,lb=3,ub=3,zoom=1,viewx=0,viewy=0;
  bool running=false;
  void run();
  void randomStart();
  void gliderStart();
  void update();
  void updateView();
private:
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
