#ifndef GAME_CLIENT_GAMESTATE_H
#define GAME_CLIENT_GAMESTATE_H

#include "Vehicle.h"
#include "Base.h"
#include <iostream>
#include <vector>

class GameState
{
private:
	std::vector<Vehicle*>* players;
	std::vector<Base*>* bases;
public:
	GameState();
	void addPlayer(Vehicle* add);
	void addBase(Base* add);
	std::vector<Vehicle*>* getPlayers();
	std::vector<Base*>* getBases();
	//TODO: populate GameState with containers (powerups, XP zone location, bases, etc.)
};

#endif //GAME_CLIENT_GAMESTATE_H
