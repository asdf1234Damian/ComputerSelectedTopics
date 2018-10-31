#!/usr/bin/env bash
echo "Cleaning Files"
#rm txtfiles/*.txt
rm txtfiles/*.wls
g++ source/generator.cpp -o source/generator
g++ source/generatorNoStillLife.cpp -o source/generatorNoStillLife

echo "Game of life"
echo "Compiling With Still Life"
source/./generator 2 2 3 3 3 >> txtfiles/LifeS2.wls
source/./generator 3 2 3 3 3 >> txtfiles/LifeS3.wls
source/./generator 4 2 3 3 3 >> txtfiles/LifeS4.wls
#source/./generator 5 2 3 3 3 >> txtfiles/LifeS5.wls
#source/./generator 6 2 3 3 3 >> txtfiles/LifeS6.wls
echo "Compiling Without Still Life"
source/./generatorNoStillLife 2 2 3 3 3 >> txtfiles/LifeS2NoStillLife.wls
source/./generatorNoStillLife 3 2 3 3 3 >> txtfiles/LifeS3NoStillLife.wls
source/./generatorNoStillLife 4 2 3 3 3 >> txtfiles/LifeS4NoStillLife.wls
#source/./generator 5 2 3 3 3 >> txtfiles/LifeS5.wls
#source/./generator 6 2 3 3 3 >> txtfiles/LifeS6.wls


echo "Diffusion"
echo "Compiling With Still Life"
source/./generator 2 7 7 2 2 >> txtfiles/DiffusionS2.wls
source/./generator 3 7 7 2 2 >> txtfiles/DiffusionS3.wls
source/./generator 4 7 7 2 2 >> txtfiles/DiffusionS4.wls
#source/./generator 5 7 7 2 2 >> txtfiles/DiffusionS5.wls
#source/./generator 6 7 7 2 2 >> txtfiles/DiffusionS6.wls
echo "Compiling Without Still Life"
g++ source/generatorNoStillLife.cpp -o source/generatorNoStillLife
source/./generatorNoStillLife 2 7 7 2 2 >> txtfiles/DiffusionS2NoStillLife.wls
source/./generatorNoStillLife 3 7 7 2 2 >> txtfiles/DiffusionS3NoStillLife.wls
source/./generatorNoStillLife 4 7 7 2 2 >> txtfiles/DiffusionS4NoStillLife.wls
#source/./generator 5 7 7 2 2 >> txtfiles/DiffusionS5.wls
#source/./generator 6 7 7 2 2 >> txtfiles/DiffusionS6.wls
chmod +x txtfiles/*.wls
