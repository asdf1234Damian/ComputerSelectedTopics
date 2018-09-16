#include "Automata.h"
#include <iostream>
#include <ctime>
#include <random>

Automata::Automata(unsigned int size):
grid({size,size},"Game of life"),
cells(size*size),
cellsNext(size*size){
  this->size=size;
  grid.setFramerateLimit(60);
  update();
}

void Automata::run(){
  randomStart();
  while (grid.isOpen()) {
    grid.clear();
    update();
    grid.draw(cells.data(),cells.size(),sf::Points);
    grid.display();
    pollEvent();
  }
}

void Automata::randomStart(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cells[y*size + x].position={(float)x,(float)y};
      if (rand()%2==1) {
        cells[y*size + x].color={250,250,250};
      }else{
        cells[y*size + x].color={0,0,0};
      }
    }
  }
}

void Automata::update(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cells[y*size + x].position={(float)x,(float)y};
      setCell(x,y);
    }
  }
}


void Automata::pollEvent(){
  sf::Event e;
  while (grid.pollEvent(e)) {
    if (e.type== sf::Event::Closed) {
      grid.close();
    }
  }
}

///////////////////////////////////////////////////////////////////////////
//                  This look more like a cell class
///////////////////////////////////////////////////////////////////////////

size_t Automata::getIndex(float x, float y){
  return (y*size + x);
}

short int Automata::getValue(float x, float y){

  if (x<0) {x=size;}else if (x>size) {x=0;}
  if (y<0) {y=size;}else if (y>size) {x=0;}

  if (cells[getIndex(x,y)].color==sf::Color(250,250,250)) {
    return 1;
  }else{
    return 0;
  }
}

short int Automata::neighSum(float x, float y){
  return(getValue(x-1,y+1)+getValue(x-1,y)+getValue(x-1,y-1)+getValue(x,y+1)+getValue(x,y-1)+getValue(x+1,y+1)+getValue(x+1,y)+getValue(x+1,y-1));

}

bool Automata::rule( float x, float y){
  if (getValue(x,y)==1) {//Is alive
    if (neighSum(x,y)>=ls&&neighSum(x,y)<=us) {
      return true;//survives
    }
  }else if (neighSum(x,y)>=lb&&neighSum(x,y)<=ub) {//Is Dead
    return true;//born
  }else{
    return false;//Dies||StaysDead
  }
}

void Automata::setCell(float x, float y){
  if (rule(x,y)) {
    cells[y*size + x].color={250,250,250};//white
  }else{
    cells[y*size + x].color={0,0,0};//black
  }
}


int main(int argc, char const *argv[]) {
  std::cout << "Size of the grid" << '\n';
  unsigned int size;
  std::cin >> size;
  Automata GOL(size);
  GOL.run();
  if (GOL.running) {
    std::cout << "Go cat" << '\n';
  }
  return 0;
}
