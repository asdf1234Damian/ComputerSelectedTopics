#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>

class Automata{
public:
  unsigned int size;
  double p;
  Automata(unsigned int,double,short int,short int,short int,short int,short int,short int);
  sf::Color antC= sf::Color(250, 0,0);
  sf::Color pheromC= sf::Color(0,0,250);
  sf::Color cleanC= sf::Color(250, 250,250);
  int zoom=1,viewx=0,viewy=0,totalAnts=0, totalPher=0, gen=1;
  void run();
  void randomStart();
  void update();
  void addAnt(int, int);
  void rotateAnt(int, int, int);
  void rotateAnt(sf::CircleShape, int);
  void moveAhead(sf::CircleShape);
  bool standing(sf::CircleShape);
  void flipCell(int x, int y);
  void updateView();

private:
  sf::RenderWindow grid;
  sf::View view;
  bool running=false;
  bool state=true;//True sets current state to A,false to B
  std::vector<sf::Vertex> cellsA;
  std::vector<sf::Vertex> cellsB;
  std::vector<sf::CircleShape> ants;
  void pollEvent();
  bool getValue(float, float);
  bool rule(float, float);
  size_t getIndex(float , float );
  void setCell(float , float );
};
