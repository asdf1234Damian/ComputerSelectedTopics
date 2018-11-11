#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <random>
#include <utility>

class Cell{
public:
  Cell();
  void CellInit(float,float);
  float x,y;
  bool state;
  sf::Color color;
  void setPosition();
private:
};



Cell::Cell(){
}

void Cell::CellInit(float x,float y){
  this->x=x;
  this->y=y;
}

class Automata{
public:
  Automata(unsigned int,double,double,double,short int,short int,short int,short int,short int,short int, short int);
  void run();
private:
  bool running=false;
  bool state=true;//True sets current state to A,false to B
  unsigned int size;
  short int zoom=1,viewx=0,viewy=0,totalAnts=0, gen=1,mode;
  double p,pq,pa;
  std::map<unsigned int, int> colorMap;
  sf::RenderWindow grid;
  std::vector<Cell> cells;
  std::vector<std::pair<sf::Color,int>> totalPher;
  std::vector<std::pair<sf::Sprite,sf::Color>> ants;
  sf::View view;
  sf::Vector2f moveAhead(sf::Sprite);
  sf::Texture workerUp, workerRight, workerLeft, workerDown;
  sf::Texture queenUp, queenRight, queenLeft, queenDown;
  sf::Texture armyUp, armyRight, armyLeft, armyDown;
  sf::Color cleanC= sf::Color(0,0,0);
  sf::Color queenC= sf::Color(250,250,0);
  sf::Color armyC= sf::Color(0,153,0);
  sf::Color pheromC= sf::Color(250, 250,250);
  sf::Sprite facing(int, int);
  void printGens();
  void addAnt(int, int, int);
  void addQueen(int, int);
  void addArmy(int, int);
  void eraseAnt(int,int);
  void rotateAnt(int, int,int);
  void rotateAnt(sf::Sprite);
  void flipCell(int x, int y);
  void flipCell(int x, int y,sf::Color);
  void updateView();
  void randomStart();
  void update();
  void Reproduce(int, int,sf::Sprite);
  void pollEvent();
  bool standing(sf::Sprite);
  bool antExist(int, int);
  bool getValue(float, float);
  bool rule(float, float);
  void setCell(float , float );
  size_t getIndex(float , float );
  int getDir(sf::Sprite);
  int antType(int x, int y);
};
