#pragma once
#include "Player.h"
class Computer :
	public Player
{
private:
	Ship* ships = NULL;
public:
	Computer();
	~Computer();

	Ship& getShip(const int index);
	void placeShips();

	bool canPlace(sf::Vector2i position, int size, int rotation);
	bool outOfBounds(sf::Vector2i position, int size, int rotation);
};

