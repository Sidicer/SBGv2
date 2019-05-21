#include "Computer.h"

Computer::Computer()
{
	this->ships = new Ship[5];
	placeShips();
}


Computer::~Computer()
{
}

Ship & Computer::getShip(const int index) {
	return this->ships[index];
}

void Computer::placeShips()
{
	srand(time(NULL));
	int temp_placed = 0, temp_x = -1, temp_y = -1, temp_rotation = 0;
	while(temp_placed < 5) {
		temp_x = rand() % 10;
		temp_y = rand() % 10;
		temp_rotation = rand() % 2;

		if (canPlace(sf::Vector2i(temp_x, temp_y), temp_placed, temp_rotation) && !outOfBounds(sf::Vector2i(temp_x,temp_y), temp_placed, temp_rotation)) {
			ships[temp_placed].set(true, temp_placed, temp_rotation, sf::Vector2i(temp_x, temp_y));
			temp_placed++;
		}
	}
}

bool Computer::colliding(sf::Vector2i position)
{
	for (int i = 0; i < 5; i++) {
		if (getShip(i).getShipPlaced()) {

			for (int s = 0; s <= getShip(i).getShipSize(); s++) {
				switch (getShip(i).getShipRotation()) {
				case 0:
					if (getShip(i).getShipPosition().x + s == position.x && getShip(i).getShipPosition().y == position.y)
						return true;

					break;
				case 1:
					if (getShip(i).getShipPosition().x == position.x && getShip(i).getShipPosition().y + s == position.y)
						return true;

					break;
				}

			}
		}
	}
	return false;
}

bool Computer::canPlace(sf::Vector2i position, int size, int rotation)
{
	for (int i = 0; i < 5; i++) {
		
		printf("trying to place first ship\n");
		if (getShip(i).getShipPlaced() && i > 0) {
			
			for (int s = 0; s <= getShip(i).getShipSize(); s++) {

				switch (getShip(i).getShipRotation()) {
				case 0:
					for (int s2 = 0; s2 <= size; s++) {
						if (rotation == 0) { // 0 0
							if (getShip(i).getShipPosition().x + s == position.x + s2 && getShip(i).getShipPosition().y == position.y)
								return false;
							else
								return true;
						}
						else { // 0 1
							if (getShip(i).getShipPosition().x + s == position.x && getShip(i).getShipPosition().y == position.y + s2)
								return false;
							else
								return true;
						}
					}
					break;
				case 1:
					for (int s2 = 0; s2 <= size; s++) {
						if (rotation == 0) { // 1 0
							if (getShip(i).getShipPosition().x == position.x + s2 && getShip(i).getShipPosition().y + s == position.y)
								return false;
							else
								return true;
						}
						else { // 1 1
							if (getShip(i).getShipPosition().x == position.x && getShip(i).getShipPosition().y + s == position.y + s2)
								return false;
							else
								return true;
						}
					}
					break;
				}

			}
		}
		else {
			return true;
		}
	
	}
}

bool Computer::outOfBounds(sf::Vector2i position, int size, int rotation)
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