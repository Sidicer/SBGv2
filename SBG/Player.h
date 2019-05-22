#pragma once

#include "Ship.h"
#include "Computer.h"

class Player : public Ship {
private:
	Ship* ships = NULL;
	bool currently_placing;
	int placing_ship_id,
		placing_rotation;

public:
	Player();
	~Player();

	Ship& getShip(const int index);

	bool isCurrentlyPlacing();
	void isCurrentlyPlacing(bool set);

	int getPlacingShipId();
	void changePlacingShipId();
	void changePlacingShipId(bool);
	void setShipRotation();

	bool canPlace(sf::Vector2i position, int size, int rotation);
	bool outOfBounds(sf::Vector2i position, int size, int rotation);

	bool receiveShot(sf::Vector2i position);
	void shoot(Computer& computer, sf::Vector2i position);
};