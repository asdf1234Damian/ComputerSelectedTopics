#include "Automata.h"

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::normal_distribution<double> distribution(0.0,1.0);
sf::RectangleShape r = sf::RectangleShape();
sf::Vertex v;
float treshhold=300;
float cellsize=.6;
void Automata::printGens(){
  for (auto elem: colorMap){
    std::cout << gen <<',' << (unsigned) sf::Color(elem.first).r <<','<< (unsigned) sf::Color(elem.first).g <<','<< (unsigned) sf::Color(elem.first).b <<','<< elem.second<< '\n';
  }
}

Automata::Automata(unsigned int size, double p,short int cr1,short int cr2,short int cg1,short int cg2,short int cb1,short int cb2, short int mode):grid({1000,1000},"Good old Lang's Ant"),cells(size*size){
  grid.setPosition(sf::Vector2i(200,100));
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this-> pheromC= sf::Color(cr1,cg1,cb1);
  this-> cleanC= sf::Color(cr2,cg2,cb2);
  this->size=size;
  this->p=p;
  this->mode=mode;

  this->workerUp.loadFromFile("images/workerU.png");
  this->workerRight.loadFromFile("images/workerR.png");
  this->workerDown.loadFromFile("images/workerD.png");
  this->workerLeft.loadFromFile("images/workerL.png");

  /*this->queenUp.loadFromFile("images/03.png");
  this->queenRight.loadFromFile("images/02.png");
  this->queenDown.loadFromFile("images/01.png");
  this->queenLeft.loadFromFile("images/04.png");

  this->repUp.loadFromFile("images/03.png");
  this->repRight.loadFromFile("images/02.png");
  this->repDown.loadFromFile("images/01.png");
  this->repLeft.loadFromFile("images/04.png");
  */
  grid.setFramerateLimit(30);
  grid.setView(view);
}
//Ant Functions/////////////////////////////////////////////
void Automata::addAnt(int x, int y){
  if (mode==0) {
    ants.push_back(Ant(workerUp,pheromC,(float)x,(float)y));
  } else {
    auto col=sf::Color(rand()%250,rand()%250,rand()%250);
    ants.push_back(Ant(workerUp,col,(float)x,(float)y));
    colorMap.insert(std::pair<int, int>(col.toInteger(),0));
  }
}

void Automata::eraseAnt(int x, int y){
  for (size_t i = 0; i < ants.size(); i++) {
    if (ants[i].body.getPosition()==sf::Vector2f(x,y)) {
      ants.erase(ants.begin()+i);
    }
  }
}

void Automata::rotateAnt(int x, int y, int angle){
  for (size_t i = 0; i < ants.size(); i++) {
    if (ants[i].body.getPosition()==sf::Vector2f(x,y)) {
      if (angle==1) {
        switch (getDir(ants[i].body)) {
          case 1:
          ants[i].body.setTexture(workerRight);
          break;

          case 2:
          ants[i].body.setTexture(workerDown);
          break;

          case 3:
          ants[i].body.setTexture(workerLeft);
          break;

          case 4:
          ants[i].body.setTexture(workerUp);
          break;
        }
      }else{
        switch (getDir(ants[i].body)) {
          case 1:
          ants[i].body.setTexture(workerLeft);
          break;

          case 2:
          ants[i].body.setTexture(workerUp);
          break;

          case 3:
          ants[i].body.setTexture(workerRight);
          break;

          case 4:
          ants[i].body.setTexture(workerDown);
          break;
        }
      }
    }
  }
}

void Automata::rotateAnt(sf::Sprite ant){
  switch (getDir(ant)) {
    case 1:
    ant.setTexture(workerRight);
    break;

    case 2:
    ant.setTexture(workerDown);
    break;

    case 3:
    ant.setTexture(workerLeft);
    break;

    case 4:
    ant.setTexture(workerUp);
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
    if (ants[i].body.getPosition().x==x && ants[i].body.getPosition().y==y){
      return 1;
    }
  }
  return 0;
}

int Automata::getDir(sf::Sprite ant){
  if (ant.getTexture()==&workerUp)
  return 1;
  if (ant.getTexture()==&workerRight)
  return 2;
  if (ant.getTexture()==&workerDown)
  return 3;
  if (ant.getTexture()==&workerLeft)
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
  if (cells[getIndex(x,y)].color==cleanC) {
    return false;
  }else{
    return true;
  }
}

void Automata::flipCell(int x, int y){
  if (getValue(x,y)!=1) {
    colorMap[pheromC.toInteger()]++;
    cells[y*size + x].color=pheromC;//white
  }else{
    colorMap[pheromC.toInteger()]--;
    cells[y*size + x].color=cleanC;//black
  }
}

void Automata::flipCell(int x, int y,sf::Color AntCol){
  if (getValue(x,y)!=1) {
    colorMap[AntCol.toInteger()]++;
    cells[y*size + x].color=AntCol;//white
  }else{
    colorMap[AntCol.toInteger()]--;
    cells[y*size + x].color=cleanC;//black
  }
}

//Init  Functions///////////////////////////////////////////

void Automata::randomStart(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {

      cells[y*size + x].x=(float)x;
      cells[y*size + x].y=(float)y;
      cells[y*size + x].color=cleanC;
      if (distribution(generator)<p) {
        totalAnts++;
        addAnt(x, y);
      }
    }
  }
  printGens();
}

void Automata::run(){
  randomStart();
  while (grid.isOpen()) {
    grid.clear(cleanC);
    for (size_t i = 0; i < size*size; i++) {
      if(cells[i].color!=cleanC){
        if (size/zoom<=treshhold) {
          r.setPosition({(float)cells[i].x,(float)cells[i].y});
          r.setSize({(float)cellsize,(float)cellsize});
          r.setFillColor(cells[i].color);
          grid.draw(r);
        }
        else {
            v= sf::Vertex({cells[i].x,cells[i].y},cells[i].color);
            grid.draw(&v,1,sf::Points);
        }

      }
    }
    for (size_t i = 0; i < ants.size(); i++) {
      grid.draw(ants[i].body );
    }
    grid.display();
    pollEvent();
  }
}

void Automata::update(){
  float x,y;
  for (size_t i = 0; i < ants.size(); i++) {
    x=ants[i].body.getPosition().x;
    y=ants[i].body.getPosition().y;
    if(standing(ants[i].body)){
      rotateAnt(x, y, 1);
    }else{
      rotateAnt(x, y, 3);
    }
    if (mode==0) {
      flipCell(x,y);
    }else{
      flipCell(x,y,ants[i].c);
    }
    if (!antExist(moveAhead(ants[i].body).x,moveAhead(ants[i].body).y)){
      ants[i].body.setPosition(moveAhead(ants[i].body));
    }
  }
  gen++;
  printGens();
  state=!state;
}

void Automata::updateView(){
  if(size/zoom==1){
    view.reset(sf::FloatRect(0, 0, size/zoom, size/zoom ));
    grid.setView(view);
  }else{
    view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
    grid.setView(view);
  }
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
