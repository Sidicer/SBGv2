#!/bin/bash
clear


g++ -c main.cpp
g++ -c Ship.cpp
g++ -c Player.cpp
g++ -c Computer.cpp

g++ -o sbg main.o Ship.o Player.o Computer.o -lsfml-graphics -lsfml-window -lsfml-system

./sbg