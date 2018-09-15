#include "Automata.h"
#include <ctime>
#include <random>

Automata::Automata():m_window({size,size},"Game of life"),m_pixels(size*size){
  m_window.setFramerateLimit(60);
  for (size_t x = 0; x < size; x++) {
    for (size_t y = 0; y < size; y++) {
      m_pixels[y*size + x].position={x,y};
      setCell(x,y,rand()%250); 
    }
  }
}

void Automata::run(){
  while (m_window.isOpen()) {
    m_window.clear();
    m_window.draw(m_pixels.data(),m_pixels.size(),sf::Points);
    m_window.display();
    pollEvent();
  }
}


void Automata::pollEvent(){
  sf::Event e;
  while (m_window.pollEvent(e)) {
    if (e.type== sf::Event::Closed) {
      m_window.close();
    }

  }
}

void Automata::setCell(int x, int y, sf::Uint8 c){
  m_pixels[y*size + x].color={c,c,c};
}


int main(int argc, char const *argv[]) {
  Automata GOL;
  GOL.run();
  return 0;
}
