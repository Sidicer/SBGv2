#include "Computer.h"

Computer::Computer()
{
	// Create a Dynamic array to store our ships
	this->ships = new Ship[5];

	// Initialize those 5 ships with their correct sizes
	for (int i = 0; i < 5; i++) {
		if (i == 0) this->ships[i].setShipSize(1);
		if (i > 0 && i < 3) this->ships[i].setShipSize(2);
		if (i == 3) this->ships[i].setShipSize(3);
		if (i == 4) this->ships[i].setShipSize(4);
	}

	placeShips();
}


Computer::~Computer()
{
}

// Returns data about the "index"ed ship from Ship class
Ship & Computer::getShip(const int index) {
	return this->ships[index];
}

// Function that places ships
void Computer::placeShips()
{
	printf("Computer is placing ships. Please wait...\n");
	// To generate more random numbers
	srand(time(NULL));
	int temp_placed = 0, temp_x = -1, temp_y = -1, temp_rotation = 0;

	// Loop through 5 ships until all of them are placed
	while(temp_placed < 5) {
		temp_x = rand() % 10;
		temp_y = rand() % 10;
		temp_rotation = rand() % 2;

		// If "canPlace" returns true and outOfBounds returns false - ship will be placed
		if (canPlace(sf::Vector2i(temp_x, temp_y), getShip(temp_placed).getShipSize(), temp_rotation) && !outOfBounds(sf::Vector2i(temp_x,temp_y), getShip(temp_placed).getShipSize(), temp_rotation)) {
			ships[temp_placed].set(true, getShip(temp_placed).getShipSize(), temp_rotation, sf::Vector2i(temp_x, temp_y));
			printf("I placed #%i ship, rotation:%i\n", temp_placed, temp_rotation);
			printf("%i:%i\n\n", temp_x, temp_y);
			temp_placed++;
		}
		else {
			printf("I didnt place #%i\n", temp_placed);
		}
	}
}

// Checks if the ship that's being placed does not intersect with an already placed ship
bool Computer::canPlace(sf::Vector2i position, int size, int rotation)
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

				} else if (getShip(i).getShipRotation() == 1 && rotation == 1) { // 1 1
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

// Checks if the ship that's being placed is out of bounds
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