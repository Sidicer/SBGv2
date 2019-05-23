#pragma once

#include "Player.h"
class Game_engine;

class Computer : public Ship
{
private:
	Ship* ships = NULL;
	sf::Vector2i last_hit;
	int last_dir;
	int con_hits;
	int hit_count;
public:
	Computer();
	~Computer();

	Ship& getShip(const int index);
	void placeShips();

	bool canPlace(sf::Vector2i position, int size, int rotation);
	bool outOfBounds(sf::Vector2i position, int size, int rotation);

	bool receiveShot(sf::Vector2i position, Game_engine &game);
	bool shoot(Player &player, Game_engine &game);
	int hitCount();
	void hitCount(bool);
};

