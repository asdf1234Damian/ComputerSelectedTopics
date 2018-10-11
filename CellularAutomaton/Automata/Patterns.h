
void Automata::gliderStart(){
  for (size_t x = 0; x < size; x++) {
    for (size_t y = 0; y < size; y++) {
      cellsA[y*size + x].position={(float)x,(float)y};
      cellsB[y*size + x].position={(float)x,(float)y};
      cellsA[y*size + x].color=dead;
    }
  }

  cellsA[20*size + 21].color=alive;
  cellsA[21*size + 22].color=alive;
  cellsA[22*size + 20].color=alive;
  cellsA[22*size + 21].color=alive;
  cellsA[22*size + 22].color=alive;
}

void Automata::exploderStart(){
  for (size_t x = 0; x < size; x++) {
    for (size_t y = 0; y < size; y++) {
      cellsA[y*size + x].position={(float)x,(float)y};
      cellsB[y*size + x].position={(float)x,(float)y};
      cellsA[y*size + x].color=dead;
      if (y>=size/2 && y<size/2+5 ) {
        if (x<size/2+5 && x>=size/2) {
          if (x==size/2||x==size/2+4) {
            cellsA[y*size + x].color=alive;
          }
          if ((y==size/2||y==size/2+4)&& x==size/2+2) {
            cellsA[y*size + x].color=alive;
          }
        }
      }
    }
  }
}
