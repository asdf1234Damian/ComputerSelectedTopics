#!/usr/bin/env bash
echo "compilando!"
g++ -c Automata.cpp
echo "Linkeando!"
g++ Automata.o -o Automata -lsfml-graphics -lsfml-window -lsfml-system
echo "Compilado!"
./Automata
