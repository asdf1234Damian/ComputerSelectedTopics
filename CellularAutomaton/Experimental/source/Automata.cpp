#include "Automata.h"

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::normal_distribution<double> distribution(0.0,1.0);
sf::RectangleShape r = sf::RectangleShape();
sf::Vertex v;
float cellsize=.6;
float treshhold=100;

Cell::Cell(){
}

void Cell::CellInit(float x,float y, bool b){
  this->x=x;
  this->y=y;
  this->state=b;
}


Automata::Automata(unsigned int size, double p,short int cr1,short int cr2,short int cg1,short int cg2,short int cb1,short int cb2,short int ls, short int us, short int lb, short int ub):grid({1000,1000},"Game of life"),cellsA(size*size),cellsB(size*size){
  grid.setPosition(sf::Vector2i(200,100));
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this->size=size;
  this->p=p;
  this-> alive= sf::Color(cr1,cg1,cb1);
  this-> dead= sf::Color(cr2,cg2,cb2);
  this->ls=ls;
  this->us=us;
  this->lb=lb;
  this->ub=ub;
  grid.setFramerateLimit(30);
  grid.setView(view);
}
//Cell Functions//////////////////////////////////////////////////
void Automata::flipCell(int x, int y){
  x=(x*size) / (zoom*grid.getSize().x);
  y=(y*size) / (zoom*grid.getSize().y);
  if (state) {
    if (getValue(x,y)!=1) {
      total++;
      cellsA[y*size + x].state=true;//white
    }else{
      cellsA[y*size + x].state=false;//black
    }
  } else {
    if (getValue(x,y)!=1) {
      total++;
      cellsB[y*size + x].state=true;//white
    }else{
      cellsA[y*size + x].state=false;//black
    }
  }
  updateView();
}


size_t Automata::getIndex(float x, float y){
  return (y*size + x);
}

short int Automata::getValue(float x, float y){
  if (x<0) {x=size-1;}else if (x>=size) {x=0;}
  if (y<0) {y=size-1;}else if (y>=size) {y=0;}
  if (state) {
    return cellsA[getIndex(x,y)].state;
  }else{
    return cellsB[getIndex(x,y)].state;
  }
}

short int Automata::neighSum(float x, float y){
  return(getValue(x-1,y+1)+getValue(x-1,y)+getValue(x-1,y-1)+getValue(x,y+1)+getValue(x,y-1)+getValue(x+1,y+1)+getValue(x+1,y)+getValue(x+1,y-1));
}

bool Automata::rule( float x, float y){
    if (getValue(x,y)==1&&neighSum(x,y)>=ls&&neighSum(x,y)<=us) {
      return true;//survives
    }else if(getValue(x,y)==0&&neighSum(x,y)>=lb&&neighSum(x,y)<=ub){
      return true;//born
    }else{
      return false;
    }
}

void Automata::setCell(float x, float y){
  if (state) {
    if (rule(x,y)) {
      total++;
      cellsB[y*size + x].state=true;//white
    }else{
      cellsB[y*size + x].state=false;//black
    }
  } else {
    if (rule(x,y)) {
      total++;
      cellsA[y*size + x].state=true;//white
    }else{
      cellsA[y*size + x].state=false;//black
    }
  }
}

//Main Loop///////////////////////////////////////////////////////
void drawVertex(){

}

void drawrect(){

}


void Automata::run(){
  randomStart();
  while (grid.isOpen()) {
    grid.clear(dead);
    if (state){
      if (size/zoom<=treshhold) {
        for (size_t i = 0; i < cellsA.size(); i++) {
          if (cellsA[i].state) {
            r.setPosition({(float)cellsA[i].x,(float)cellsA[i].y});
            r.setSize({(float)cellsize,(float)cellsize});
            r.setFillColor(alive);
            grid.draw(r);
          }
        }
      } else {
        for (size_t i = 0; i < cellsA.size(); i++) {
          if (cellsA[i].state) {
            v= sf::Vertex({cellsA[i].x,cellsA[i].y},alive);
            grid.draw(&v,1,sf::Points);
          }
        }
      }
    }else{
      if (size/zoom<=treshhold) {
        for (size_t i = 0; i < cellsB.size(); i++) {
          if (cellsB[i].state) {
            r.setPosition({(float)cellsB[i].x,(float)cellsB[i].y});
            r.setSize({(float)cellsize,(float)cellsize});
            r.setFillColor(alive);
            grid.draw(r);
          }
        }
      } else {
        for (size_t i = 0; i < cellsB.size(); i++) {
          if (cellsB[i].state) {
            v= sf::Vertex({cellsB[i].x,cellsB[i].y},alive);
            grid.draw(&v,1,sf::Points);
          }
        }
      }
    }
    grid.display();
    pollEvent();
  }
}

void Automata::randomStart(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      cellsB[y*size + x].CellInit(x,y,false);
      if (distribution(generator)<p) {
        total++;
        cellsA[y*size + x].CellInit(x,y,true);
      }else{
        cellsA[y*size + x].CellInit(x,y,false);
      }
    }
  }
  std::cout <<gen<<", "<<total<< '\n';
  total=0;
}

void Automata::update(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      setCell(x,y);
    }
  }
  gen++;
  std::cout <<gen<<", "<<total<< '\n';
  total=0;
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
      if (e.mouseButton.button == sf::Mouse::Left){
        flipCell(e.mouseButton.x,e.mouseButton.y);
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
          viewx-=10;
          updateView();
        }
        break;

        case sf::Keyboard::D:
        if((unsigned)viewx<=size-size/zoom){
          viewx+=10;
          updateView();
        }
        break;

        case sf::Keyboard::S:
        if((unsigned)viewy<size-size/zoom){
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
  unsigned int size=strtoul(argv[1], NULL,10);
  double p=strtod(argv[2], NULL);
  short int cr1=strtoul(argv[3], NULL,10),cg1=strtoul(argv[4], NULL,10),cb1=strtoul(argv[5], NULL,10),cr2=strtoul(argv[6], NULL,10),cg2=strtoul(argv[7], NULL,10),cb2=strtoul(argv[8], NULL,10),ls=strtoul(argv[9], NULL,10),us=strtoul(argv[10], NULL,10),lb=strtoul(argv[11], NULL,10),ub=strtoul(argv[12], NULL,10);
  Automata GOL(size,p,cr1,cr2,cg1,cg2,cb1,cb2,ls,us,lb,ub);
  GOL.run();
  return 0;
}
