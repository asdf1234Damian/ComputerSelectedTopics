#!/usr/bin/env bash
g++ source/generator.cpp -o generator.o
 ./generator.o $1 2 3 3 3
# ./generator.o $1 7 7 2 2
