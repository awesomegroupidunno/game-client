#ifndef GAME_CLIENT_GAMESTATE_H
#define GAME_CLIENT_GAMESTATE_H

#include "Vehicle.h"
#include <iostream>
#include <vector>

class GameState
{
private:
	std::vector<Vehicle*>* players;

public:
	GameState();

	void addPlayer(Vehicle* add);
	std::vector<Vehicle*>* getPlayers();
	//TODO: populate GameState with containers (powerups, XP zone location, bases, etc.)
};

#endif //GAME_CLIENT_GAMESTATE_H
