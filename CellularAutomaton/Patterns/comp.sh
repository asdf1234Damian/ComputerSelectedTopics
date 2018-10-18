#!/usr/bin/env bash
echo "Cleaning Files"
rm txtfiles/*.txt
echo "Compiling With Still Life"
g++ source/generator.cpp -o generator
#./generator 2 2 3 3 3 >> txtfiles/LifeS2.txt
#./generator 3 2 3 3 3 >> txtfiles/LifeS3.txt
./generator 4 2 3 3 3 >> txtfiles/LifeS4.txt
#./generator 5 2 3 3 3 >> LifeS5.txt
#./generator 6 2 3 3 3 >> LifeS6.txt
echo "Compiling Without Still Life"
g++ source/generatorNoStillLife.cpp -o generatorNoStillLife
#./generatorNoStillLife 2 2 3 3 3 >> txtfiles/LifeS2NoStillLife.txt
#./generatorNoStillLife 3 2 3 3 3 >> txtfiles/LifeS3NoStillLife.txt
./generatorNoStillLife 4 2 3 3 3 >> txtfiles/LifeS4NoStillLife.txt
#./generator 5 2 3 3 3 >> LifeS5.txt
#./generator 6 2 3 3 3 >> LifeS6.txt
