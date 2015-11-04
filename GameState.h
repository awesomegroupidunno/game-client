#ifndef GAME_CLIENT_GAMESTATE_H
#define GAME_CLIENT_GAMESTATE_H

#include "Vehicle.h"
#include "Base.h"
#include "Bullet.h"
#include <iostream>
#include <vector>

class GameState
{
private:
	std::vector<Vehicle*>* players;
	std::vector<Base*>* bases;
	std::vector<Bullet*>* bullets;
public:
	GameState();
	void addPlayer(Vehicle* add);
	void addBase(Base* add);
	void addBullet(Bullet* add);
	std::vector<Vehicle*>* getPlayers();
	std::vector<Base*>* getBases();
	std::vector<Bullet*>* getBullets();
	//TODO: populate GameState with containers (powerups, XP zone location, bases, etc.)
};

#endif //GAME_CLIENT_GAMESTATE_H
