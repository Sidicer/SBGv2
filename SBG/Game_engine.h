#pragma once

class Game_engine
{
private:
	int who_is_shooting;
public:
	Game_engine();
	~Game_engine();

	int whoIsShooting();
	int whoIsShooting(bool);
};

