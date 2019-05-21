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

bool Player::canPlace(sf::Vector2i position, int size, int rotation)
{
	bool temp_canplace = false;
	for (int i = 0; i < 5; i++)
	{
		//printf("I'm checking if I can place a ship compared to %i\n", i);
		for (int size_1 = 0; size_1 <= getShip(i).getShipSize(); size_1++)
		{
			//printf("I found ship`s #%i size: %i\n", i, getShip(i).getShipSize());
			for (int size_2 = 0; size_2 <= size; size_2++)
			{
				//printf("I'm looping through placable ship size: %i\n", size_2);
				if (getShip(i).getShipRotation() == 0 && rotation == 0) { // 0 0
					//printf("First ships rotation is %i, second ship is 0\n", getShip(i).getShipRotation());
					if ((getShip(i).getShipPosition().x + size_1) == (position.x + size_2) && getShip(i).getShipPosition().y == position.y)
					{
						//printf("I cannot place because: %i:%i intersects %i:%i\n", (getShip(i).getShipPosition().x + size_1), getShip(i).getShipPosition().y, (position.x + size_2),position.y);
						return false;
					}
					else
					{
						//printf("I can place because: %i:%i doesnt intersect %i:%i\n", (getShip(i).getShipPosition().x + size_1), getShip(i).getShipPosition().y, (position.x + size_2), position.y);
						temp_canplace = true;
					}

				}
				else if (getShip(i).getShipRotation() == 1 && rotation == 1) { // 1 1
				 //printf("First ships rotation is %i, second ship is 1\n", getShip(i).getShipRotation());
					if (getShip(i).getShipPosition().x == position.x && (getShip(i).getShipPosition().y + size_1) == (position.y + size_2))
					{
						//printf("I cannot place because: %i:%i intersects %i:%i\n", getShip(i).getShipPosition().x, (getShip(i).getShipPosition().y + size_1),position.x,(position.y + size_2));
						return false;
					}
					else
					{
						//printf("I can place because: %i:%i doesnt intersect %i:%i\n", getShip(i).getShipPosition().x, (getShip(i).getShipPosition().y + size_1), position.x, (position.y + size_2));
						temp_canplace = true;
					}

				}
				else if (getShip(i).getShipRotation() == 0 && rotation == 1) { // 0 1
					//printf("First ships rotation is %i, second ship is 1\n", getShip(i).getShipRotation());
					if ((getShip(i).getShipPosition().x + size_1) == position.x && getShip(i).getShipPosition().y == (position.y + size_2))
					{
						//printf("I cannot place because: %i:%i intersects %i:%i\n", (getShip(i).getShipPosition().x + size_1), getShip(i).getShipPosition().y,position.x,(position.y + size_2));
						return false;
					}
					else
					{
						//printf("I can place because: %i:%i doesnt intersect %i:%i\n", (getShip(i).getShipPosition().x + size_1), getShip(i).getShipPosition().y, position.x, (position.y + size_2));
						temp_canplace = true;
					}

				}
				else if (getShip(i).getShipRotation() == 1 && rotation == 0) { // 1 0
					//printf("First ships rotation is %i, second ship is 0\n", getShip(i).getShipRotation());
					if (getShip(i).getShipPosition().x == (position.x + size_2) && (getShip(i).getShipPosition().y + size_1) == position.y)
					{
						//printf("I cannot place because: %i:%i intersects %i:%i\n", getShip(i).getShipPosition().x, (getShip(i).getShipPosition().y + size_1),(position.x + size_2),position.y);
						return false;
					}
					else
					{
						//printf("I can place because: %i:%i doesnt intersect %i:%i\n", getShip(i).getShipPosition().x, (getShip(i).getShipPosition().y + size_1), (position.x + size_2), position.y);
						temp_canplace = true;
					}

				}
			}
		}

	}
	return temp_canplace;
}

bool Player::outOfBounds(sf::Vector2i position, int size, int rotation)
{
	for (int i = 0; i < 5; i++) {
		for (int s = 0; s <= size; s++) {

			switch (rotation) {
			case 0:
				if (position.x + s >= 10 || position.y >= 10)
					return true;

				break;
			case 1:
				if (position.x >= 10 || position.y + s >= 10)
					return true;

				break;
			}
		}
	}
	return false;
}