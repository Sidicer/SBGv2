#include "Player.h"

Player::Player() {
	this->ships = new Ship[5];
	this->currently_placing = false;
}

Player::~Player() {
	delete[] this->ships;
	this->ships = NULL;
}

Ship & Player::getShip(const int index) {
	return this->ships[index];
}

bool Player::isCurrentlyPlacing() {	return this->currently_placing; }

void Player::isCurrentlyPlacing(bool set) { this->currently_placing = set; }

bool Player::colliding(sf::Vector2i position)
{
	for (int i = 0; i < 5; i++) {
		for (int s = 0; s <= getShip(i).getShipSize(); s++) {
			switch (getShip(i).getShipRotation()) {
			case 0:
				if (getShip(i).getShipPosition().x + s == position.x && getShip(i).getShipPosition().y == position.y)
					return true;

				break;
			case 1:
				if (getShip(i).getShipPosition().x == position.x && getShip(i).getShipPosition().y + s== position.y)
					return true;

				break;
			}
		}
	}
	return false;
}
