#include <SFML/Graphics.hpp>
#include <vector>
class Automata{
public:
  unsigned int size,p;
  Automata(unsigned int,short int,short int,short int,short int,short int,short int,short int );
  sf::Color alive= sf::Color(250, 250,250);
  sf::Color dead= sf::Color(0,0,0);
  int ls=2,us=3,lb=3,ub=3,zoom=1,viewx=0,viewy=0,total=0, gen=1;
  void run();
  void randomStart();
  void gliderStart();
  void exploderStart();
  void update();
  void updateView();
private:
  sf::RenderWindow grid;
  sf::View view;
  bool running=false;
  bool state=true;//True sets current state to A,false to B
  std::vector<sf::Vertex> cellsA;
  std::vector<sf::Vertex> cellsB;
  void pollEvent();
  short int getValue(float, float);
  short int neighSum(float, float );
  bool rule(float, float);
  size_t getIndex(float , float );
  void setCell(float , float );
};
