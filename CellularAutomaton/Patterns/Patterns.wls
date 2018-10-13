#!/usr/bin/env wolframscript
(* ::Package:: *)

(*Game of Life size 2 Toroid*)
(* With Still Life*)
edgesData = OpenRead["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/txtfiles/LifeS2.txt"]
Export["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/Graphs/LifeS2.png",Read[edgesData,Expression]]
Close[edgesData]
(*Without Still Life *)
edgesData = OpenRead["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/txtfiles/LifeS2NoStillLife.txt"]
Export["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/Graphs/LifeS2NSL.png",Read[edgesData,Expression]]
Close[edgesData]
(*Game of Life size 3 Toroid*)
(* With Still Life*)
edgesData = OpenRead["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/txtfiles/LifeS3.txt"]
Export["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/Graphs/LifeS3.png",Read[edgesData,Expression]]
Close[edgesData]
(*Without Still Life *)
edgesData = OpenRead["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/txtfiles/LifeS3NoStillLife.txt"]
Export["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/Graphs/LifeS3NSL.png",Read[edgesData,Expression]]
Close[edgesData]
(*Game of Life size 4 Toroid*)
(* With Still Life*)
edgesData = OpenRead["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/txtfiles/LifeS4.txt"]
Export["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/Graphs/LifeS4.png",Read[edgesData,Expression]]
Close[edgesData]
(*Without Still Life *)
edgesData = OpenRead["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/txtfiles/LifeS4NoStillLife.txt"]
Export["Documents/ComputerSelectedTopics/CellularAutomaton/Patterns/Graphs/LifeS4NSL.png",Read[edgesData,Expression]]
Close[edgesData]







