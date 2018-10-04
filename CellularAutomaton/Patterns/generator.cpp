// C++ program to generate n-bit Gray codes
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
unsigned int size;
short us,ls,ub,lb;

//Auxiliar function for getting the 2d position in the 1d
int getIndex(int x, int y){
  return y*size+x;
}
//Auxiliar fucntion for toroid structure of the grid/////////////////
int getVal(std::string perm, int x, int y){
  if (x<0) {x=size-1;}else if (x>=(int)size) {x=0;}
  if (y<0) {y=size-1;}else if (y>=(int)size) {y=0;}
  if (perm[getIndex(x,y)]=='1') {
    return 1;
  }
  return 0;
}

int neighSum(std::string perm, int x, int y){
  return(getVal(perm,x-1,y+1)+getVal(perm,x-1,y)+getVal(perm,x-1,y-1)+getVal(perm,x,y+1)+getVal(perm,x,y-1)+getVal(perm,x+1,y+1)+getVal(perm,x+1,y)+getVal(perm,x+1,y-1));
}

bool rule(short int x, short int y, std::string perm){
  if (getVal(perm,x,y)&&neighSum(perm, x, y)>=ls&&neighSum(perm, x, y)<=us) {
      return true;
  }else if (!getVal(perm,x,y)&&neighSum(perm, x, y)>=lb&&neighSum(perm, x, y)<=ub) {
      return true;
  }else{
    return false;
  }
}

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
//flipflop in line 855
int main(int argc, char const *argv[]) {
//////////////////////////////////////////////////////////////////////////////
  freopen("nextState.tmp","w+",stdout);//Output file
  size = std::stoi(argv[1]);
  ls = std::stoi(argv[2]);
  us = std::stoi(argv[3]);
  lb = std::stoi(argv[4]);
  ub = std::stoi(argv[5]);
///////////Generates the square matrix of size 'size' with 'i' 1s in it///////
  for (size_t i = 0; i <= size*size; i++) {
    std::string perm;
    for (size_t j = 0; j < size*size-i; j++) {
      perm.append("0");
    }
    for (size_t k = 0; k <i; k++) {
      perm.append("1");
    }
//////////////////////////////////////////////////////////////////////////////
    do{
      std::cout << perm << ", " <<  nextState(perm) <<'\n';
    }while (std::next_permutation(perm.begin(),perm.end()));
  }

}
