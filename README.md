# Computer Selected Topics (Complex Systems)

This repository is mainly used for the projects and assingments of the Computer Selected Topics course at ESCOM IPN. 

Student: Meza Madrid Raúl Damián 

Programs
* Cellular Automaton 
* Cellular Automaton with composite function and memory
* Langtons Ant
* Patterns in Life & Difussion

Requirements:
Most of the programs use the SFML 2.5.0 library  (https://www.sfml-dev.org) for CPP graphics. Even though the main GUI is made in Python. For more info about how to install SFML, please read: https://www.sfml-dev.org/download/sfml/2.5.0.

All folders include a source folder, where all source code and temporal files can be found along with a script called comp.sh used to compile and link the required libraries. 

Running: 
To run the programs, each folder includes a run.sh script. The GUI is in charge of running the CPP graphics, but the latter can be run independantly with coustom parameters. The last line in the comp.sh script you can find an example as a comment. Where the parameter are the following 

* Automata:
  * 1,Size of the space
  * 2, z-value for normal distribution probability
  * 3,4,5, RGB value for the color of living cell
  * 6,7,8, RGB value for the color of dead cells
  * 9,10,11,12, rule for the Automata 

Example:

`$ ./Automata 400 -1.28155 250 250 250 0 0 0 2 3 3 3`
