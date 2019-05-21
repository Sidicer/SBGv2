#include "Ship.h"

Ship::Ship() {
	this->ship_is_placed = false;
	this->ship_size = 0;
	this->ship_rotation = 0;
	this->ship_position.x = -1;
	this->ship_position.y = -1;
}

Ship::~Ship() {
}

bool Ship::getShipPlaced() { return this->ship_is_placed; }

int Ship::getShipSize() { return this->ship_size; }

int Ship::getShipRotation() { return this->ship_rotation; }

sf::Vector2i Ship::getShipPosition() { return this->ship_position; }

void Ship::set(bool placed, int size, int rotation, sf::Vector2i position)
{
	this->ship_is_placed = placed;
	this->ship_size = size;
	this->ship_rotation = rotation;
	this->ship_position = position;
}

void Ship::setShipPlaced(bool placed) { this->ship_is_placed = placed; }

void Ship::setShipSize(int size) { this->ship_size = size; }

void Ship::setShipRotation(int rotation) { this->ship_rotation = rotation; }

void Ship::setShipPosition(sf::Vector2i position) { this->ship_position = position; }