#include "AutomataQueens.h"

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
Automata::Automata(unsigned int size, double p,double pa,double pq,short int cr1,short int cr2,short int cg1,short int cg2,short int cb1,short int cb2, short int mode):grid({1000,1000},"Good old Lang's Ant"),cells(size*size){
  grid.setPosition(sf::Vector2i(200,100));
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this-> pheromC= sf::Color(cr1,cg1,cb1);
  this-> cleanC= sf::Color(cr2,cg2,cb2);
  this->size=size;
  this->p=p;
  this->pa=pa;
  this->pq=pq;
  this->mode=mode;

  this->workerUp.loadFromFile("images/workerU.png");
  this->workerRight.loadFromFile("images/workerR.png");
  this->workerDown.loadFromFile("images/workerD.png");
  this->workerLeft.loadFromFile("images/workerL.png");


  this->queenUp.loadFromFile("images/queenU.png");
  this->queenRight.loadFromFile("images/queenR.png");
  this->queenDown.loadFromFile("images/queenD.png");
  this->queenLeft.loadFromFile("images/queenL.png");

  this->armyUp.loadFromFile("images/armyU.png");
  this->armyRight.loadFromFile("images/armyR.png");
  this->armyDown.loadFromFile("images/armyD.png");
  this->armyLeft.loadFromFile("images/armyL.png");

  grid.setFramerateLimit(30);
  grid.setView(view);
}
//Ant Functions/////////////////////////////////////////////
void Automata::addQueen(int x, int y){
    sf::Sprite body =sf::Sprite();
    body.setTexture(queenUp);
    body.setScale(.003, .003);
    body.setPosition((float) x, (float) y);
    std::pair<sf::Sprite, sf::Color> ant(body,queenC);
    ants.push_back(ant);
}

void Automata::addArmy(int x, int y){
    sf::Sprite body =sf::Sprite();
    body.setTexture(armyUp);
    body.setScale(.003, .003);
    body.setPosition((float) x, (float) y);
    std::pair<sf::Sprite, sf::Color> ant(body,armyC);
    ants.push_back(ant);
}

void Automata::addAnt(int x, int y, int mode){
    sf::Sprite body =sf::Sprite();
    body.setTexture(workerUp);
    body.setScale(.003, .003);
    body.setPosition((float) x, (float) y);
    std::pair<sf::Sprite, sf::Color> ant(body,pheromC);
    if(!mode){
      ants.push_back(ant);
    }else{
      ants.insert(ants.begin(),ant);
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
          ants[i].first.setTexture(workerRight);
          break;

          case 2:
          ants[i].first.setTexture(workerDown);
          break;

          case 3:
          ants[i].first.setTexture(workerLeft);
          break;

          case 4:
          ants[i].first.setTexture(workerUp);
          break;

          case 5:
          ants[i].first.setTexture(armyRight);
          break;

          case 6:
          ants[i].first.setTexture(armyDown);
          break;

          case 7:
          ants[i].first.setTexture(armyLeft);
          break;

          case 8:
          ants[i].first.setTexture(armyUp);
          break;

          case 9:
          ants[i].first.setTexture(queenRight);
          break;

          case 10:
          ants[i].first.setTexture(queenDown);
          break;

          case 11:
          ants[i].first.setTexture(queenLeft);
          break;

          case 12:
          ants[i].first.setTexture(queenUp);
          break;
        }
      }else{
        switch (getDir(ants[i].first)) {
          case 1:
          ants[i].first.setTexture(workerLeft);
          break;

          case 2:
          ants[i].first.setTexture(workerUp);
          break;

          case 3:
          ants[i].first.setTexture(workerRight);
          break;

          case 4:
          ants[i].first.setTexture(workerDown);
          break;

          case 5:
          ants[i].first.setTexture(armyLeft);
          break;

          case 6:
          ants[i].first.setTexture(armyUp);
          break;

          case 7:
          ants[i].first.setTexture(armyRight);
          break;

          case 8:
          ants[i].first.setTexture(armyDown);
          break;

          case 9:
          ants[i].first.setTexture(queenLeft);
          break;

          case 10:
          ants[i].first.setTexture(queenUp);
          break;

          case 11:
          ants[i].first.setTexture(queenRight);
          break;

          case 12:
          ants[i].first.setTexture(queenDown);
          break;
        }
      }
    }
  }
}

sf::Vector2f Automata::moveAhead(sf::Sprite ant){
  float x=ant.getPosition().x;
  float y=ant.getPosition().y;
  switch (getDir(ant)) {
    case 1:
    case 5:
    case 9:
    y++;
    break;

    case 2:
    case 6:
    case 10:
    x++;
    break;

    case 3:
    case 7:
    case 11:
    y--;
    break;

    case 4:
    case 8:
    case 12:
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
  if (ant.getTexture()==&workerUp)
  return 1;
  if (ant.getTexture()==&workerRight)
  return 2;
  if (ant.getTexture()==&workerDown)
  return 3;
  if (ant.getTexture()==&workerLeft)
  return 4;
  if (ant.getTexture()==&armyUp)
  return 5;
  if (ant.getTexture()==&armyRight)
  return 6;
  if (ant.getTexture()==&armyDown)
  return 7;
  if (ant.getTexture()==&armyLeft)
  return 8;
  if (ant.getTexture()==&queenUp)
  return 9;
  if (ant.getTexture()==&queenRight)
  return 10;
  if (ant.getTexture()==&queenDown)
  return 11;
  if (ant.getTexture()==&queenLeft)
  return 12;

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

void Automata::flipCell(int x, int y,sf::Color AntCol){
  if (getValue(x,y)!=1) {
    colorMap[AntCol.toInteger()]++;
    cells[y*size + x].color=AntCol;//white
  }else{
    colorMap[AntCol.toInteger()]--;
    cells[y*size + x].color=cleanC;//black
  }
}

int Automata::antType(int x, int y){
  for (size_t i = 0; i <ants.size(); i++) {
    if (ants[i].first.getPosition().x==x && ants[i].first.getPosition().y==y){
      if(ants[i].first.getTexture()==&workerDown||
      ants[i].first.getTexture()==&workerUp||
      ants[i].first.getTexture()==&workerLeft||
      ants[i].first.getTexture()==&workerRight){
        return 1;
      }else if(ants[i].first.getTexture()==&armyDown||
      ants[i].first.getTexture()==&armyUp||
      ants[i].first.getTexture()==&armyLeft||
      ants[i].first.getTexture()==&armyRight){
        return 2;
      }else{
        return 3;
      }
    }
  }
  return 0;
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
        auto temp = distribution(generator);
        if (temp <pq) {
          addQueen(x,y);
        }else if (temp<(pa+pq)) {
          addArmy(x,y);
        }else{
          addAnt(x,y,0);
        }
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
      grid.draw(ants[i].first );
    }
    grid.display();
    pollEvent();
  }
}

sf::Sprite Automata::facing(int x, int y){
    for (size_t i = 0; i <ants.size(); i++) {
    if (ants[i].first.getPosition().x==x && ants[i].first.getPosition().y==y){
      return ants[i].first;
    }
  }
}

void Automata::Reproduce(int x, int y, sf::Sprite q){
  if(getDir(q)==9){
    if(getDir(facing(x,y+1))==7){
      addAnt(x,y-1,1);
    }
  }

  if(getDir(q)==10){
    if(getDir(facing(x+1,y))==8){
      addAnt(x-1,y,1);
    }
  }

  if(getDir(q)==11){
    if(getDir(facing(x,y-1))==5){
      addAnt(x,y+1,1);
    }
  }

  if(getDir(q)==12){
    if(getDir(facing(x-1,y))==6){
      addAnt(x+1,y,1);
    }
  }
}

void Automata::update(){
  float x,y;
  for (size_t i = 0; i < ants.size(); i++) {
    x=ants[i].first.getPosition().x;
    y=ants[i].first.getPosition().y;
    if(antType(x,y)==3){
      Reproduce(x,y,ants[i].first);
    }
    if(standing(ants[i].first)){
      rotateAnt(x, y, 1);
    }else{
      rotateAnt(x, y, 3);
    }
      flipCell(x,y,ants[i].second);
    if (!antExist(moveAhead(ants[i].first).x,moveAhead(ants[i].first).y)){
      ants[i].first.setPosition(moveAhead(ants[i].first));
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
        switch (antType(x,y)){
          case 0:
            addAnt(x,y,0);
          break;

          case 1:
            eraseAnt(x,y);
            addArmy(x,y);
          break;

          case 2:
            eraseAnt(x,y);
            addQueen(x,y);
          break;

          case 3:
            eraseAnt(x,y);
          break;
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
  double pa=strtod(argv[10], NULL);
  double pq=strtod(argv[11], NULL);
  //Colors
  short int cr1=strtoul(argv[3], NULL,10),cg1=strtoul(argv[4], NULL,10),cb1=strtoul(argv[5], NULL,10),cr2=strtoul(argv[6], NULL,10),cg2=strtoul(argv[7], NULL,10),cb2=strtoul(argv[8], NULL,10), mode = strtoul(argv[9], NULL,10);
  //Initialization
  Automata GOL(size,p,pa,pq,cr1,cr2,cg1,cg2,cb1,cb2,mode);
  GOL.run();
  return 0;
}
