#pragma once

#include "Ship.h"

class Player : public Ship {
private:
	Ship* ships = NULL;
	bool currently_placing;
public:
	Player();
	~Player();

	Ship& getShip(const int index);

	bool isCurrentlyPlacing();
	void isCurrentlyPlacing(bool set);

	bool colliding(sf::Vector2i position);
};