#include "Game_engine.h"

Game_engine::Game_engine() {
	this->who_is_shooting = 1;
}

Game_engine::~Game_engine()
{
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

