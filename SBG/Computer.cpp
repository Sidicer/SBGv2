#include "Computer.h"
#include "Game_engine.h"

Computer::Computer()
{
	// Create a Dynamic array to store our ships
	this->ships = new Ship[5];
	this->last_hit = sf::Vector2i(-1,-1);
	this->con_hits = 0;
	this->last_dir = 0;
	this->hit_count = 0;

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
	//printf("Computer is placing ships. Please wait...\n");
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
			//printf("I placed #%i ship, rotation:%i\n", temp_placed, temp_rotation);
			//printf("%i:%i\n\n", temp_x, temp_y);
			temp_placed++;
		}
		else {
			//printf("I didnt place #%i\n", temp_placed);
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

bool Computer::receiveShot(sf::Vector2i position, Game_engine &game)
{
	if (!outOfBounds(position, 0, 0)) {
		bool temp_bool = false;
		//printf("recieving shot at %i:%i\n", position);
		if (canPlace(position, 0, 0)) {
			game.miss(position);
			temp_bool = false;
			return false;
		}
		else
		{
			if (game.getHit().size() == 0) {
				temp_bool = true;
			}
			else
			{
				for (size_t i = 0; i < game.getHit().size(); i++)
				{
					//printf("for %i - Does %i:%i equal %i:%i? Size: %i\n", i, position, game.getHit()[i], game.getHit().size());
					if (position == game.getHit()[i]) {
						temp_bool = false;
						return false;
					}
					else
					{
						temp_bool = true;
					}
				}
			}
		}
		if (!temp_bool) { return false; }
		else {
			printf("Computer: You hit my ship!\n");
			game.hit(position);
		}
	}
}

bool Computer::shoot(Player& player, Game_engine &game)
{
	srand(time(NULL));
	sf::Vector2i temp_position;
	int temp_dir = 0;
	if (this->last_hit.x < 0) {
		temp_position.x = rand() % 9 + 10;
		temp_position.y = rand() % 10;
		
	}
	else if (con_hits == 0) {
		temp_position.x = rand() % 9 + 10;
		temp_position.y = rand() % 10;
	}
	else if (con_hits == 1) {
		temp_dir = rand() % 3 + 1;
		switch (temp_dir) {
		case 1:
			temp_position.x = last_hit.x;
			temp_position.y = last_hit.y - 1;
			break;
		case 2:
			temp_position.x = last_hit.x + 1;
			temp_position.y = last_hit.y;
			break;
		case 3:
			temp_position.x = last_hit.x;
			temp_position.y = last_hit.y + 1;
			break;
		case 4:
			temp_position.x = last_hit.x - 1;
			temp_position.y = last_hit.y;
			break;
		}
	}
	else if (con_hits > 1) {
		switch (this->last_dir) {
		case 1:
			temp_position.x = last_hit.x;
			temp_position.y = last_hit.y - 1;
			break;
		case 2:
			temp_position.x = last_hit.x + 1;
			temp_position.y = last_hit.y;
			break;
		case 3:
			temp_position.x = last_hit.x;
			temp_position.y = last_hit.y + 1;
			break;
		case 4:
			temp_position.x = last_hit.x - 1;
			temp_position.y = last_hit.y;
			break;
		}
	}

	for (size_t i = 0; i < game.getMiss().size(); i++)
	{
		if (temp_position == game.getMiss()[i]) {
			return false;
		}
	}

	for (size_t i = 0; i < game.getHit().size(); i++)
	{
		if (temp_position == game.getHit()[i]) {
			return false;
		}
	}

	printf("last hit: %i:%i, con hits: %i, last dir: %i\n", this->last_hit, this->con_hits, this->last_dir);
	//printf("Computer: I tried to shoot at %i:%i\n", temp_position);
	if (player.receiveShot(temp_position, game)) {
		if (this->con_hits > 0 && this->con_hits < 3) this->last_dir = temp_dir;

		this->last_hit = temp_position;
		this->con_hits++;
		hitCount(true);
	}
	else {
		this->last_hit.x = -1;
		this->con_hits = 0;
	}

	return true;
}

int Computer::hitCount()
{
	return this->hit_count;
}

void Computer::hitCount(bool)
{
	this->hit_count++;
}