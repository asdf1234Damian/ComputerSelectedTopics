#include <iostream>
#include <string>
#include <algorithm>

unsigned int size;//Size of the array
short us,ls,ub,lb;//Parameter for the rule

//Auxiliar function for getting the 2d position in the 1d
int getIndex(int x, int y){
  return y*size+x;
}
//Auxiliar fucntion for toroid structure of the grid
int getVal(std::string perm, int x, int y){
  if (x<0) {x=size-1;}else if (x>=(int)size) {x=0;}
  if (y<0) {y=size-1;}else if (y>=(int)size) {y=0;}
  if (perm[getIndex(x,y)]=='1') {
    return 1;
  }
  return 0;
}

//Gets the sum of the Moove Neightborhood
int neighSum(std::string perm, int x, int y){
  return(getVal(perm,x-1,y+1)+getVal(perm,x-1,y)+getVal(perm,x-1,y-1)+getVal(perm,x,y+1)+getVal(perm,x,y-1)+getVal(perm,x+1,y+1)+getVal(perm,x+1,y)+getVal(perm,x+1,y-1));
}

//Compares neighSum value with the ones in the rule
bool rule(short int x, short int y, std::string perm){
  if (getVal(perm,x,y)&&neighSum(perm, x, y)>=ls&&neighSum(perm, x, y)<=us) {
      return true;
  }else if (!getVal(perm,x,y)&&neighSum(perm, x, y)>=lb&&neighSum(perm, x, y)<=ub) {
      return true;
  }else{
    return false;
  }
}

//Returns the String for the next state of the automaton
std::string nextState(std::string cPerm){
  std::string nPerm(size*size,'0');
  for (size_t y = 0; y < size; y++) {
    for (size_t x = 0; x < size; x++) {
      if (rule(x, y, cPerm)) {
        nPerm[getIndex(x,y)]='1';
      }
    }
  }
  return nPerm;
}

//Main Program
int main(int argc, char const *argv[]) {
  //Get parameters form the terminal
  size = (unsigned int)std::stoi(argv[1]);
  ls = std::stoi(argv[2]);
  us = std::stoi(argv[3]);
  lb = std::stoi(argv[4]);
  ub = std::stoi(argv[5]);
  //Redirects the stdout stream to a the nextState.tmp file
  //freopen(name.c_str(),"w+",stdout);
//Generates the array of size 'size*size' with 'i' 1s in it
std::string perm;
bool changed,isFinal=true;
std::cout << "Graph[{";
  for (size_t i = 0; i <=  size*size; i++) {
    perm="";
    for (size_t j = 0; j <  size*size-i; j++) {
      perm.append("0");
    }
    for (size_t k = 0; k <i; k++) {
      perm.append("1");
    }
    //Print all permutations of the current string
    //along with the next state
    do{
      if (perm!=nextState(perm)) {
        changed=true;
        std::cout << perm << " \\[UndirectedEdge] " <<  nextState(perm);
      }else{
        changed=false;
      }

      isFinal=std::next_permutation(perm.begin(),perm.end());
      if (isFinal&&changed){
        std::cout << ", ";
      }
    }while (isFinal);
    if (i!=size*size&&changed){
      std::cout << ", ";
    }
  }
std::cout << "}, VertexStyle -> Red]" << '\n';
}
