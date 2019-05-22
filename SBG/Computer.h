#pragma once

#include "Player.h"
class Game_engine;

class Computer : public Ship
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

	bool receiveShot(sf::Vector2i position, Game_engine &game);
	void shoot(Player &player, Game_engine &game);
};

