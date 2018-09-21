#include "Automata.h"
#include <iostream>
#include <ctime>
#include <random>

Automata::Automata(unsigned int size, short int p):
grid({800,800},"Game of life"),
cellsA(size*size),
cellsB(size*size){
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this->size=size;
  this->p=p;
  grid.setFramerateLimit(30);
  grid.setView(view);
  randomStart();
}

void Automata::run(){
  randomStart();
  while (grid.isOpen()) {
    grid.clear();
    if (state) {
      grid.draw(cellsA.data(),cellsA.size(),sf::Points);
    }else{
      grid.draw(cellsB.data(),cellsB.size(),sf::Points);
    }
    grid.display();
    pollEvent();
  }
}

void Automata::gliderStart(){
  for (size_t x = 0; x < size; x++) {
    for (size_t y = 0; y < size; y++) {
      cellsA[y*size + x].color=dead;
      if (y>=size/2 && y<size/2+5 ) {
        if (x<size/2+5 && x>=size/2) {
          if (x==size/2||x==size/2+4) {
            cellsA[y*size + x].color=alive;
          }
          if ((y==size/2||y==size/2+4)&& x==size/2+2) {
            cellsA[y*size + x].color=alive;
          }
        }
      }
    }
  }
}

void Automata::randomStart(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cellsA[y*size + x].position={(float)x,(float)y};
      cellsB[y*size + x].position={(float)x,(float)y};
      if (rand()%100<p) {
        cellsA[y*size + x].color=alive;
      }else{
        cellsA[y*size + x].color=dead;
      }
    }
  }

}

void Automata::update(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      setCell(x,y);
    }
  }
  state=!state;
}

void Automata::updateView(){
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  grid.setView(view);
}

void Automata::pollEvent(){
  sf::Event e;
  if (running) {
    update();
  }
  while (grid.pollEvent(e)) {
    if (e.type== sf::Event::Closed) {
      grid.close();
    }else if(e.type==sf::Event::KeyPressed){
      switch (e.key.code) {
        case sf::Keyboard::Right:
        update();
        break;

        case sf::Keyboard::Up:
        zoom++;
        updateView();
        break;

        case sf::Keyboard::Down:
        if (zoom>1) {
          zoom--;
          updateView();
        }
        break;

        case sf::Keyboard::A:
        if(viewx>0){
          viewx-=10;
          updateView();
        }
        break;

        case sf::Keyboard::D:
        if(viewx<=size-size/zoom){
          viewx+=10;
          updateView();
        }
        break;

        case sf::Keyboard::S:
        if(viewy<size-size/zoom){
          viewy+=10;
          updateView();
        }
        break;

        case sf::Keyboard::W:
        if(viewy>0){
          viewy-=10;
          updateView();
        }
        break;

        case sf::Keyboard::Left:
        running=!running;
        break;
      default:
          break;
      }

    }
    //std::cout << viewx<<":"<< viewy << '\n';
  }
}


size_t Automata::getIndex(float x, float y){
  return (y*size + x);
}

short int Automata::getValue(float x, float y){
  if (x<0) {x=size;}else if (x>size) {x=0;}
  if (y<0) {y=size;}else if (y>size) {x=0;}
  if (state) {
    if (cellsA[getIndex(x,y)].color==alive) {
      return 1;
    }else{
      return 0;
    }
  }else{
    if (cellsB[getIndex(x,y)].color==alive) {
      return 1;
    }else{
      return 0;
    }
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
  if (state) {
    if (rule(x,y)) {
      cellsB[y*size + x].color=alive;//white
    }else{
      cellsB[y*size + x].color=dead;//black
    }
  } else {
    if (rule(x,y)) {
      cellsA[y*size + x].color=alive;//white
    }else{
      cellsA[y*size + x].color=dead;//black
    }
  }
}


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  unsigned int size=strtoul(argv[1], NULL,10);
  short int p=strtoul(argv[2], NULL,10);
  Automata GOL(size,p);
  GOL.run();
  return 0;
}
