#include "Automata.h"
std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
std::normal_distribution<double> distribution(0.0,1.0);
sf::RectangleShape r = sf::RectangleShape();
sf::Vertex v;
float cellsize=.6;
float treshhold=100;
int index;
Automata::Automata(unsigned int memory, unsigned int size, double p,short int cr1,short int cr2,short int cg1,short int cg2,short int cb1,short int cb2,short int ls, short int us, short int lb, short int ub, short int ruleMode):grid({1000,1000},"Game of life"),Cells(size*size*memory),secundaryfn(&Automata::minRule){
  for(size_t t = 0; t < memory; t++){
    for (size_t y = 0; y < size; y++){
      for (size_t x = 0; x < size; x++) {
        Cells[getIndex(x,y,t)].setState(false);
      }
    }
  }
  grid.setPosition(sf::Vector2i(200,100));
  view.reset(sf::FloatRect(viewx, viewy, size/zoom, size/zoom ));
  this->memory= memory;
  this->size=size;
  this->p=p;
  this->alive= sf::Color(cr1,cg1,cb1);
  this->dead= sf::Color(cr2,cg2,cb2);
  this->ls=ls;
  this->us=us;
  this->lb=lb;
  this->ub=ub;
  grid.setFramerateLimit(30);
  grid.setView(view);
  this->current=0;
  this->next=1;

  switch (ruleMode) {
    case 0:
     secundaryfn = std::mem_fn(&Automata::minRule);
    break;

    case 1:
      secundaryfn = std::mem_fn(&Automata::maxRule);
    break;

    case 2:
      secundaryfn = std::mem_fn(&Automata::parityRule);
    break;

    default:
    break;
  }
}
//Cell Functions//////////////////////////////////////////////////
void Automata::flipCell(int x, int y){
  x=(x*size) / (zoom*grid.getSize().x);
  y=(y*size) / (zoom*grid.getSize().y);
  if (getValue(x,y)!=1) {
    total++;
    Cells[getIndex(x,y,current)].state=true;//white
  }else{
    total--;
    Cells[getIndex(x,y,current)].state=false;//black
  }
}

size_t Automata::getIndex(float x, float y,float t){
  return (t*size*size + y*size + x);
}

short int Automata::getValue(float x, float y){
  if (x<0) {x=size-1;}else if (x>=size) {x=0;}
  if (y<0) {y=size-1;}else if (y>=size) {y=0;}
  return Cells[getIndex(x,y,current)].state;
}

short int Automata::neighSum(float x, float y){
  return(getValue(x-1,y+1)+getValue(x-1,y)+getValue(x-1,y-1)+getValue(x,y+1)+getValue(x,y-1)+getValue(x+1,y+1)+getValue(x+1,y)+getValue(x+1,y-1));
}

bool Automata::mainRule(float x, float y){
    if (getValue(x,y)==1&&neighSum(x,y)>=ls&&neighSum(x,y)<=us) {
      return true;//survives
    }else if(getValue(x,y)==0&&neighSum(x,y)>=lb&&neighSum(x,y)<=ub){
      return true;//born
    }else{
      return false;
    }
}

bool Automata::minRule(float x, float y){
  for (size_t t = 0; t < current; t++) {
    if (!Cells[getIndex(x,y,t)].state) {
      return false;
    }
  }
  return true;
}

bool Automata::maxRule(float x, float y){
  for (size_t t = 0; t < current; t++) {
    if (Cells[getIndex(x,y,t)].state) {
      return true;
    }
  }
  return false;
}

bool Automata::parityRule(float x, float y){
  bool result = Cells[getIndex(x,y,0)].state;
  for (size_t t = 1; t < current; t++) {
      result ^= Cells[getIndex(x,y,t)].state;
  }
  return !result;
}

void Automata::setCell(float x, float y){
  if (next==0){
    if (secundaryfn(this,x,y)) {
      total++;
      Cells[getIndex(x,y,next)].state=true;//white
    }else{
      Cells[getIndex(x,y,next)].state=false;//black
    }
  } else {
    if (mainRule(x,y)) {
      total++;
      Cells[getIndex(x,y,next)].state=true;//white
    }else{
      Cells[getIndex(x,y,next)].state=false;//black
    }
  }
}

//Main Loop///////////////////////////////////////////////////////
void Automata::run(){
  randomStart();
  while (grid.isOpen()) {
    grid.clear(dead);
      if (size/zoom<=treshhold) {
        for (size_t y = 0; y < size; y++) {
          for (size_t x = 0; x < size; x++) {
            index = getIndex(x,y,current);
            if (Cells[index].state) {
              r.setPosition({(float)x,(float)y});
              r.setSize({(float)cellsize,(float)cellsize});
              r.setFillColor(alive);
              grid.draw(r);
            }
          }
        }
      } else {
        for (size_t y = 0; y < size; y++) {
          for (size_t x = 0; x < size; x++) {
            index = getIndex(x,y,current);
            if (Cells[index].state) {
              v= sf::Vertex({(float)x,(float)y},alive);
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
    for (size_t y = 0; y < size; y++) {
      for (size_t x = 0; x < size; x++){
      if (distribution(generator)<p) {
        total++;
        Cells[getIndex(x,y,current)].setState(true);
      }
    }
  }
  std::cout <<gen<<", "<<total<< '\n';
  total=0;
}

void Automata::update(){
  for (size_t x = 0; x < size; x++){
    for (size_t y = 0; y < size; y++) {
      setCell(x,y);//TODO
    }
  }
  gen++;
  std::cout <<gen<<", "<<total<< '\n';
  total=0;
  current=next;
  next=(current+1)%memory;
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
  freopen("gens","w+",stdout);
  unsigned int memory=strtoul(argv[1], NULL,10);
  unsigned int size=strtoul(argv[2], NULL,10);
  double   p=strtod(argv[3], NULL);
  short int cr1=strtoul(argv[4], NULL,10),cg1=strtoul(argv[5], NULL,10),cb1=strtoul(argv[6], NULL,10),cr2=strtoul(argv[7], NULL,10),cg2=strtoul(argv[8], NULL,10),cb2=strtoul(argv[9], NULL,10),ls=strtoul(argv[10], NULL,10),us=strtoul(argv[11], NULL,10),lb=strtoul(argv[12], NULL,10),ub=strtoul(argv[13], NULL,10),srule=strtoul(argv[14], NULL,10);
  Automata GOL(memory,size,p,cr1,cr2,cg1,cg2,cb1,cb2,ls,us,lb,ub,srule);
  GOL.run();
  return 0;
}
