#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <random>
#include <utility>

class Automata{
public:
  unsigned int size;
  double p;
  Automata(unsigned int,double,short int,short int,short int,short int,short int,short int, short int);
  sf::Texture antUp;
  sf::Texture antRight;
  sf::Texture antLeft;
  sf::Texture antDown;
  sf::Color cleanC= sf::Color(0,0,0);
  sf::Color pheromC= sf::Color(250, 250,250);
  short int zoom=1,viewx=0,viewy=0,totalAnts=0, totalPher=0, gen=1,mode;
  void run();
private:
  void addAnt(int, int);
  int getDir(sf::Sprite);
  void eraseAnt(int,int);
  void rotateAnt(int, int,int);
  void rotateAnt(sf::Sprite);
  sf::Vector2f moveAhead(sf::Sprite);
  bool standing(sf::Sprite);
  bool antExist(int, int);
  void flipCell(int x, int y);
  void flipCell(int x, int y,sf::Color);
  void updateView();
  void randomStart();
  void update();
  sf::RenderWindow grid;
  sf::View view;
  bool running=false;
  bool state=true;//True sets current state to A,false to B
  std::vector<sf::RectangleShape> cells;
  std::vector<std::pair<sf::Sprite,sf::Color>> ants;
  void pollEvent();
  bool getValue(float, float);
  bool rule(float, float);
  size_t getIndex(float , float );
  void setCell(float , float );
};
