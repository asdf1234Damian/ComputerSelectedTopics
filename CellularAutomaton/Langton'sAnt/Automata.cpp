#include "Automata.h"

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::normal_distribution<double> distribution(0.0,1.0);


Automata::Automata(unsigned int size, double p,short int cr1,short int cr2,short int cg1,short int cg2,short int cb1,short int cb2, short int mode):grid({1000,1000},"Good old Lang's Ant"),cells(size*size){
  grid.setPosition(sf::Vector2i(200,100));
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this-> pheromC= sf::Color(cr1,cg1,cb1);
  this-> cleanC= sf::Color(cr2,cg2,cb2);
  this->size=size;
  this->p=p;
  this->mode=mode;
  this->antUp.loadFromFile("images/03.png");
  this->antRight.loadFromFile("images/02.png");
  this->antDown.loadFromFile("images/01.png");
  this->antLeft.loadFromFile("images/04.png");
  grid.setFramerateLimit(30);
  grid.setView(view);
}
//Ant Functions/////////////////////////////////////////////
void Automata::addAnt(int x, int y){
  if (mode==0) {
    sf::Sprite body =sf::Sprite();
    body.setTexture(antUp);
    body.setScale(.003, .003);
    body.setPosition((float) x, (float) y);
    std::pair<sf::Sprite, sf::Color> ant(body,pheromC);
    ants.push_back(ant);
  } else {
    sf::Sprite body =sf::Sprite();
    body.setTexture(antUp);
    body.setScale(.003, .003);
    body.setPosition((float) x, (float) y);
    std::pair<sf::Sprite, sf::Color> ant(body,sf::Color(rand()%250,rand()%250,rand()%250));
    ants.push_back(ant);
  }
}

void Automata::eraseAnt(int x, int y){
  for (size_t i = 0; i < ants.size(); i++) {
    if (ants[i].first.getPosition()==sf::Vector2f(x,y)) {
      ants.erase(ants.begin()+i);
    }
  }
}

void Automata::rotateAnt(int x, int y, int angle){
  for (size_t i = 0; i < ants.size(); i++) {
    if (ants[i].first.getPosition()==sf::Vector2f(x,y)) {
      if (angle==1) {
        switch (getDir(ants[i].first)) {
          case 1:
          ants[i].first.setTexture(antRight);
          break;

          case 2:
          ants[i].first.setTexture(antDown);
          break;

          case 3:
          ants[i].first.setTexture(antLeft);
          break;

          case 4:
          ants[i].first.setTexture(antUp);
          break;
        }
      }else{
        switch (getDir(ants[i].first)) {
          case 1:
          ants[i].first.setTexture(antLeft);
          break;

          case 2:
          ants[i].first.setTexture(antUp);
          break;

          case 3:
          ants[i].first.setTexture(antRight);
          break;

          case 4:
          ants[i].first.setTexture(antDown);
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
  if (x<0) {x=size-1;}else if (x>=size) {x=0;}
  if (y<0) {y=size-1;}else if (y>=size) {y=0;}
  return sf::Vector2f(x,y);
}

//Aux Functions/////////////////////////////////////////////

bool Automata::antExist(int x, int y){
  for (size_t i = 0; i <ants.size(); i++) {
    if (ants[i].first.getPosition().x==x && ants[i].first.getPosition().y==y){
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

bool Automata::standing(sf::Sprite ant){
  return getValue(ant.getPosition().x,ant.getPosition().y);
}

size_t Automata::getIndex(float x, float y){
  return (y*size + x);
}

bool Automata::getValue(float x, float y){
  if (x<0) {x=size-1;}else if (x>=size) {x=0;}
  if (y<0) {y=size-1;}else if (y>=size) {y=0;}
  if (cells[getIndex(x,y)].getFillColor()==cleanC) {
    return false;
  }else{
    return true;
  }
}

void Automata::flipCell(int x, int y){
  if (getValue(x,y)!=1) {
    totalPher++;
    cells[y*size + x].setFillColor(pheromC);//white
  }else{
    totalPher--;
    cells[y*size + x].setFillColor(cleanC);//black
  }
}

void Automata::flipCell(int x, int y,sf::Color AntCol){
  if (getValue(x,y)!=1) {
    totalPher++;
    cells[y*size + x].setFillColor(AntCol);//white
  }else{
    totalPher--;
    cells[y*size + x].setFillColor(cleanC);//black
  }
}

//Init  Functions///////////////////////////////////////////

void Automata::randomStart(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cells[y*size + x].setPosition({(float)x,(float)y});
      cells[y*size + x].setSize({(float)1000/size,(float)1000/size});
      cells[y*size + x].setFillColor(cleanC);
      if (distribution(generator)<p) {
        totalAnts++;
        addAnt(x, y);
      }
    }
  }
  std::cout <<gen<<", "<< totalPher<< '\n';
}

void Automata::run(){
  randomStart();
  auto border=sf::RectangleShape ({(float)size-1,(float)size-1});
  border.setPosition({0,0});
  border.setOutlineColor(sf::Color({250,0,0}));
  border.setOutlineThickness(.2);
  while (grid.isOpen()) {
    grid.clear(cleanC);
    grid.draw(border);
    for (size_t i = 0; i < size*size; i++) {
      grid.draw(cells[i]);
    }
    for (size_t i = 0; i < ants.size(); i++) {
      grid.draw(ants[i].first );
    }
    grid.display();
    pollEvent();
  }
}

void Automata::update(){
  float x,y;
  for (size_t i = 0; i < ants.size(); i++) {
    x=ants[i].first.getPosition().x;
    y=ants[i].first.getPosition().y;
    if(standing(ants[i].first)){
      rotateAnt(x, y, 1);
    }else{
      rotateAnt(x, y, 3);
    }
    if (mode==0) {
      flipCell(x,y);
    }else{
      flipCell(x,y,ants[i].second);
    }
    if (!antExist(moveAhead(ants[i].first).x,moveAhead(ants[i].first).y)){
      ants[i].first.setPosition(moveAhead(ants[i].first));
    }
  }
  gen++;
  std::cout <<gen<<", "<<totalPher<< '\n';
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
      int x=((e.mouseButton.x)*size) / (zoom*grid.getSize().x)+viewx;
      int y=((e.mouseButton.y)*size) / (zoom*grid.getSize().y)+viewy;

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
          viewx-=size/(zoom*10);
          updateView();
        break;

        case sf::Keyboard::D:
          viewx+=size/(zoom*10);
          updateView();
        break;

        case sf::Keyboard::S:
          viewy+=size/(zoom*10);
          updateView();
        break;

        case sf::Keyboard::W:
          viewy-=size/(zoom*10);
          updateView();
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

//Main Program//////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  freopen("gens","w+",stdout);
  //Size
  unsigned int size=strtoul(argv[1], NULL,10);
  //Probability
  double p=strtod(argv[2], NULL);
  //Colors
  short int cr1=strtoul(argv[3], NULL,10),cg1=strtoul(argv[4], NULL,10),cb1=strtoul(argv[5], NULL,10),cr2=strtoul(argv[6], NULL,10),cg2=strtoul(argv[7], NULL,10),cb2=strtoul(argv[8], NULL,10), mode = strtoul(argv[9], NULL,10);
  //Initialization
  Automata GOL(size,p,cr1,cr2,cg1,cg2,cb1,cb2,mode);
  GOL.run();
  return 0;
}
