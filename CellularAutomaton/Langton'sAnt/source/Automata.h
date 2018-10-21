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
  Automata(unsigned int,double,short int,short int,short int,short int,short int,short int, short int);
  void run();
private:
  bool running=false;
  bool state=true;//True sets current state to A,false to B
  unsigned int size;
  short int zoom=1,viewx=0,viewy=0,totalAnts=0, gen=1,mode;
  double p;
  std::map<unsigned int, int> colorMap;
  sf::RenderWindow grid;
  std::vector<sf::RectangleShape> cells;
  std::vector<std::pair<sf::Color,int>> totalPher;
  std::vector<std::pair<sf::Sprite,sf::Color>> ants;
  sf::View view;
  sf::Vector2f moveAhead(sf::Sprite);
  sf::Texture workerUp, workerRight, workerLeft, workerDown;
  sf::Texture queenUp, queenRight, queenLeft, queenDown;
  sf::Texture repUp, repRight, repLeft, repDown;
  sf::Color cleanC= sf::Color(0,0,0);
  sf::Color pheromC= sf::Color(250, 250,250);
  void printGens();
  void addAnt(int, int);
  void eraseAnt(int,int);
  void rotateAnt(int, int,int);
  void rotateAnt(sf::Sprite);
  void flipCell(int x, int y);
  void flipCell(int x, int y,sf::Color);
  void updateView();
  void randomStart();
  void update();
  void pollEvent();
  bool standing(sf::Sprite);
  bool antExist(int, int);
  bool getValue(float, float);
  bool rule(float, float);
  void setCell(float , float );
  size_t getIndex(float , float );
  int getDir(sf::Sprite);
};
