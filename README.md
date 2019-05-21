# Sidicers Battleship Game v2.0

Object oriented battleship game I am making for university. It uses SFML 2.5, but minimally, whole brains are in pure C++11.0+
The game is Computer vs Player only.

## Some info

Every ship holds only 5 variables. Positions are just 2D arrays of x's and y's (comfrom 0 to 9), then the Size of the ship (1-4),
Rotation of the ship (0-1) and a Boolean that registers if the ship is placed or not.

Computer places every ship itself when the game starts
