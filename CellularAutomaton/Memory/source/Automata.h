#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>

class Cell{
public:
  Cell();
  void setState(bool);
  bool state;
private:
};

Cell::Cell(){
}

void Cell::setState( bool b){
  this->state=b;
}

class Automata{
public:
  Automata(unsigned int, unsigned int,double,short int,short int,short int,short int,short int,short int,short int, short int, short int, short int);
  void run();
private:
  sf::Color alive= sf::Color(250, 250,250);
  sf::Color dead= sf::Color(0,0,0);
  int ls=2,us=3,lb=3,ub=3,zoom=1,viewx=0,viewy=0,total=0, gen=1;
  unsigned int size,memory,current,next;
  double p;
  void randomStart();
  void plot();
  void update();
  void flipCell(int, int);
  void updateView();
  sf::RenderWindow grid;
  sf::View view;
  bool running=false;
  bool state=true;//True sets current state to A,false to B
  std::vector<Cell> Cells;
  void pollEvent();
  short int getValue(float, float);
  short int neighSum(float, float);
  bool mainRule(float, float);
  bool minRule(float, float);
  bool maxRule(float, float);
  bool parityRule(float, float);
  size_t getIndex(float , float , float);
  void setCell(float , float);
};
