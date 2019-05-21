#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Ship {
private:
	bool ship_is_placed;
    int ship_size,
        ship_rotation;
	sf::Vector2i ship_position;

public:
	Ship();
	~Ship();

	bool getShipPlaced();
    int getShipSize();
    int getShipRotation();
	sf::Vector2i getShipPosition();

	void set(bool placed, int size, int rotation, sf::Vector2i position);
	void setShipPlaced(bool placed);
    void setShipSize(int size);
    void setShipRotation(int rotation);
	void setShipPosition(sf::Vector2i position);
};