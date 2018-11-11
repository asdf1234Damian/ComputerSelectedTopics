#!/usr/bin/env bash
echo "compilando!"
g++ -c AutomataQueens.cpp
echo "Linkeando!"
g++ AutomataQueens.o -o AutomataQueens -lsfml-graphics -lsfml-window -lsfml-system
echo "Compilado!"
#./Automata 10 -1.28155 250 250 250 0 0 0 1
