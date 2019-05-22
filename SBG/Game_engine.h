#pragma once

#include "Computer.h"

class Game_engine
{
private:
	std::vector<sf::Vector2i> hitShips;
	std::vector<sf::Vector2i> missShips;
	int who_is_shooting;

public:
	Game_engine();
	~Game_engine();

	int whoIsShooting();
	int whoIsShooting(bool);
	void hit(sf::Vector2i position);
	void miss(sf::Vector2i position);
	const std::vector<sf::Vector2i>& getHit() const;
	const std::vector<sf::Vector2i>& getMiss() const;
};

