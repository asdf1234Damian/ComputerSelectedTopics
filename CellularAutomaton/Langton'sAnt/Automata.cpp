#include "Automata.h"
//#include "Patterns.h"

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::normal_distribution<double> distribution(0.0,1.0);

Automata::Automata(unsigned int size, double p,short int cr1,short int cr2,short int cg1,short int cg2,short int cb1,short int cb2):grid({1000,1000},"Good old Lang's Ant"),cellsA(size*size),cellsB(size*size){
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this->size=size;
  this->p=p;
  this->antUp.loadFromFile("images/01.png");
  this->antRight.loadFromFile("images/02.png");
  this->antDown.loadFromFile("images/03.png");
  this->antLeft.loadFromFile("images/04.png");
  grid.setFramerateLimit(30);
  grid.setView(view);
}
//Ant Functions///////////////////////////////////////////////////
void Automata::addAnt(int x, int y){
  sf::Sprite ant =sf::Sprite();
  ant.setTexture(antUp);
  ant.setScale(.003, .003);
  ant.setPosition((float) x, (float) y);
  ants.push_back(ant);
}

void Automata::eraseAnt(int x, int y){
  x=(x*size) / (zoom*grid.getSize().x);
  y=(y*size) / (zoom*grid.getSize().y);
  for (size_t i = 0; i < ants.size(); i++) {
    if (ants[i].getPosition()==sf::Vector2f(x,y)) {
      ants.erase(ants.begin()+i);
    }
  }
}

//Cell Functions//////////////////////////////////////////////////
size_t Automata::getIndex(float x, float y){
  return (y*size + x);
}

bool Automata::getValue(float x, float y){
  if (x<0) {x=size-1;}else if (x>=size) {x=0;}
  if (y<0) {y=size-1;}else if (y>=size) {y=0;}

  if (state) {
    if (cellsA[getIndex(x,y)].color==pheromC) {
      return true;
    }else{
      return false;
    }
  }else{
    if (cellsB[getIndex(x,y)].color==pheromC) {
      return true;
    }else{
      return false;
    }
  }
}

bool Automata::rule( float x, float y){
    //TODO
    return false;
}

/*void Automata::setCell(sf::Circle){
  if (state) {
    if (standing(sf::Sprite)) {
      totalPher++;
      cellsB[y*size + x].color=pheromC;//white
    }else{
      cellsB[y*size + x].color=cleanC;//black
    }
  } else {
    if (rule(x,y)) {
      totalPher++;
      cellsA[y*size + x].color=pheromC;//white
    }else{
      cellsA[y*size + x].color=cleanC;//black
    }
  }
}
*/
//Main Loop///////////////////////////////////////////////////////
//Where things are drawn//////////////////////////////////////////

void Automata::run(){
  randomStart();
  while (grid.isOpen()) {
    grid.clear(cleanC);
    for (size_t i = 0; i < ants.size(); i++) {
      grid.draw(ants[i]);
    }
    if (state){
      grid.draw(cellsA.data(),cellsA.size(),sf::Points);

    }else{
      grid.draw(cellsB.data(),cellsB.size(),sf::Points);
    }
    grid.display();
    pollEvent();
  }
}

void Automata::randomStart(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cellsA[y*size + x].position={(float)x,(float)y};
      cellsB[y*size + x].position={(float)x,(float)y};
      cellsA[y*size + x].color=cleanC;
      cellsB[y*size + x].color=cleanC;
      //addAnt(x,y);
      /*
      if (distribution(generator)<p) {
        totalAnts++;
        addAnt(x, y);
      }
      */
    }
  }
  std::cout <<gen<<", "<< totalPher<< '\n';
  totalAnts=0;
}

bool Automata::antExist(int x, int y){
  for (size_t i = 0; i <ants.size(); i++) {
    if (ants[i].getPosition().x==x && ants[i].getPosition().y==y){
      return 1;
    }
  }
  return 0;
}

int Automata::getDir(sf::Sprite ant){
  if (ant.getTexture()==&antUp)
    return 1;
  if (ant.getTexture()==&antRight)
    return 2;
  if (ant.getTexture()==&antDown)
    return 3;
  if (ant.getTexture()==&antLeft)
    return 4;
  return 0;
}

void Automata::flipCell(int x, int y){
  if (state) {
    if (getValue(x,y)!=1) {
      totalPher++;
      cellsB[y*size + x].color=pheromC;//white
    }else{
      cellsB[y*size + x].color=cleanC;//black
    }
  } else {
    if (getValue(x,y)!=1) {
      totalPher++;
      cellsA[y*size + x].color=pheromC;//white
    }else{
      cellsA[y*size + x].color=cleanC;//black
    }
  }
  updateView();
}

bool Automata::standing(sf::Sprite ant){
  return getValue(ant.getPosition().x,ant.getPosition().y);
}

void Automata::rotateAnt(int x, int y, int angle){
  for (size_t i = 0; i < ants.size(); i++) {
    if (ants[i].getPosition()==sf::Vector2f(x,y)) {
      if (angle==1) {
        switch (getDir(ants[i])) {
          case 1:
          ants[i].setTexture(antRight);
          break;

          case 2:
            ants[i].setTexture(antDown);
          break;

          case 3:
            ants[i].setTexture(antLeft);
          break;

          case 4:
            ants[i].setTexture(antUp);
          break;
        }
      }else{
        switch (getDir(ants[i])) {
          case 1:
          ants[i].setTexture(antLeft);
          break;

          case 2:
            ants[i].setTexture(antUp);
          break;

          case 3:
            ants[i].setTexture(antRight);
          break;

          case 4:
            ants[i].setTexture(antDown);
          break;
        }
      }

    }
  }
}

void Automata::rotateAnt(sf::Sprite ant){
  switch (getDir(ant)) {
    case 1:
      ant.setTexture(antRight);
    break;

    case 2:
      ant.setTexture(antDown);
    break;

    case 3:
      ant.setTexture(antLeft);
    break;

    case 4:
      ant.setTexture(antUp);
    break;
  }
}

sf::Vector2f Automata::moveAhead(sf::Sprite ant){
  float x=ant.getPosition().x;
  float y=ant.getPosition().y;
  switch (getDir(ant)) {
    case 1:
      y++;
    break;

    case 2:
      x++;
    break;

    case 3:
      y--;
    break;

    case 4:
      x--;
    break;
  }
  return sf::Vector2f(x,y);
}
void Automata::update(){
  float x,y;
  for (size_t i = 0; i < ants.size(); i++) {
    x=ants[i].getPosition().x;
    y=ants[i].getPosition().y;
    if(standing(ants[i])){
      rotateAnt(x, y, 1);
    }else{
      rotateAnt(x, y, 3);
    }
    flipCell(x,y);
    ants[i].setPosition(moveAhead(ants[i]));
  }
  gen++;
  std::cout <<gen<<", "<<totalPher<< '\n';
  totalPher=0;
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
    }else if (e.type == sf::Event::MouseButtonPressed){
      int x=(e.mouseButton.x*size) / (zoom*grid.getSize().x);
      int y=(e.mouseButton.y*size) / (zoom*grid.getSize().y);

      if (e.mouseButton.button == sf::Mouse::Left){
        if (antExist(x,y)) {
          eraseAnt(x,y);
        }else{
          addAnt(x,y);
        }
      }else if(e.mouseButton.button == sf::Mouse::Right){
        rotateAnt(x,y,90);
      }

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
          viewx-=size/(zoom*10);
          updateView();
        }
        break;

        case sf::Keyboard::D:
        if((unsigned)viewx<=size-size/zoom){
          viewx+=size/(zoom*10);
          updateView();
        }
        break;

        case sf::Keyboard::S:
        if((unsigned)viewy<size-size/zoom){
          viewy+=size/(zoom*10);
          updateView();
        }
        break;

        case sf::Keyboard::W:
        if(viewy>0){
          viewy-=size/(zoom*10);
          updateView();
        }
        break;

        case sf::Keyboard::Left:
        running = !running;
        break;

        default:
        break;
      }
    }
  }
}

//Main Program////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  //freopen("gens","w+",stdout);
  //Size
  unsigned int size=strtoul(argv[1], NULL,10);
  //Probability
  double p=strtod(argv[2], NULL);
  //Colors
  short int cr1=strtoul(argv[3], NULL,10),cg1=strtoul(argv[4], NULL,10),cb1=strtoul(argv[5], NULL,10),cr2=strtoul(argv[6], NULL,10),cg2=strtoul(argv[7], NULL,10),cb2=strtoul(argv[8], NULL,10);
  //Initialization
  Automata GOL(size,p,cr1,cr2,cg1,cg2,cb1,cb2);
  GOL.run();
  return 0;
}
