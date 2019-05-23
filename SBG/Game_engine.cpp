#include "Game_engine.h"

Game_engine::Game_engine() {
	this->who_is_shooting = 1;
}

Game_engine::~Game_engine()
{
	printf("*** game_engine destructor ***\n");
	printf("size of hitShips: %i\n", hitShips.size());
	for (size_t i = 0; i < hitShips.size(); i++)
	{
		printf("%i:%i ", hitShips[i]);
		if (i % 4 == 0 && i !=0 ) printf("\n");
	}
	printf("*** ====================== ***\n");
}

int Game_engine::whoIsShooting()
{
	return this->who_is_shooting;
}

int Game_engine::whoIsShooting(bool change)
{
	this->who_is_shooting = (this->who_is_shooting == 0) ? 1 : 0;
	return 0;
}

void Game_engine::hit(sf::Vector2i position)
{
	hitShips.push_back(position);
}

void Game_engine::miss(sf::Vector2i position)
{
	missShips.push_back(position);
}

const std::vector<sf::Vector2i>& Game_engine::getHit() const
{
	return hitShips;
}

const std::vector<sf::Vector2i>& Game_engine::getMiss() const
{
	return missShips;
}

