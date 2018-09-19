#include "Automata.h"
#include <iostream>
#include <ctime>
#include <random>

Automata::Automata(unsigned int size, short int p):
grid({size,size},"Difussion Rule"),
cells(size*size),
cellsNext(size*size){
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this->size=size;
  this->p=p;
  grid.setFramerateLimit(30);
  grid.setView(view);
  update();
}

void Automata::run(){
  randomStart();
  /*
  gliderStart();
  */
  while (grid.isOpen()) {
    grid.clear();
    grid.draw(cells.data(),cells.size(),sf::Points);
    grid.display();
    pollEvent();
  }
}


void Automata::gliderStart(){

  for (size_t x = 0; x < size; x++) {
    for (size_t y = 0; y < size; y++) {
      cells[y*size + x].color=dead;
      if (y>=size/2 && y<size/2+5 ) {
        if (x<size/2+5 && x>=size/2) {
          if (x==size/2||x==size/2+4) {
            cells[y*size + x].color=alive;
          }
          if ((y==size/2||y==size/2+4)&& x==size/2+2) {
            cells[y*size + x].color=alive;
          }

          /*
          if ((x>=size/2&&x<=size/2+2)&&y==size/2) {
            cells[y*size + x].color=alive;
          }
          */
        }
      }


    }
  }
}


void Automata::randomStart(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cells[y*size + x].position={(float)x,(float)y};
      if (rand()%100<p) {
        cells[y*size + x].color=alive;
      }else{
        cells[y*size + x].color=dead;
      }
    }
  }

}

void Automata::update(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cells[y*size + x].position={(float)x,(float)y};
      cellsNext[y*size + x].position={(float)x,(float)y};
      setCell(x,y);
    }
  }
  cells=cellsNext;
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
        if(viewx>10){
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
        if(viewy>10){
          viewy-=10;
          updateView();
        }
        break;

        case sf::Keyboard::Left:
        if (running) {
          running=false;
        }else{
          running=true;
        }
        break;
      default:
          break;
      }

    }
    //std::cout << viewx<<":"<< viewy << '\n';
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

  if (cells[getIndex(x,y)].color==alive) {
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
    cellsNext[y*size + x].color=alive;//white
  }else{
    cellsNext[y*size + x].color=dead;//black
  }
}


int main(int argc, char const *argv[]) {
  std::cout << "Size of the grid" << '\n';
  unsigned int size;
  std::cin >> size;
  std::cout << "Probability of starting as alive" << '\n';
  short int p;
  std::cin >> p;
  Automata GOL(size,p);
  GOL.run();
  return 0;
}
