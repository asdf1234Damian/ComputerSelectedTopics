#!/usr/bin/env bash
echo "compilando"
g++ -c test.cpp
echo "Linkeando"
g++ test.o -o test -lsfml-graphics -lsfml-window -lsfml-system

echo "Ejecutando"
./test
