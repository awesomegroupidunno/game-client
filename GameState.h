#ifndef GAME_CLIENT_GAMESTATE_H
#define GAME_CLIENT_GAMESTATE_H

#include "Vehicle.h"
#include "Base.h"
#include "Bullet.h"
#include "Shield.h"
#include "Generator.h"
#include <iostream>
#include <vector>

class GameState
{
private:
	std::vector<Vehicle*>* players;
	std::vector<Base*>* bases;
	std::vector<Bullet*>* bullets;
	std::vector<Shield*>* shields;
	std::vector<Generator*>* generators;
public:
	GameState();
	void addPlayer(Vehicle* add);
	void addBase(Base* add);
	void addBullet(Bullet* add);
	void addShield(Shield* add);
	void addGenerator(Generator* add);
	std::vector<Vehicle*>* getPlayers();
	std::vector<Base*>* getBases();
	std::vector<Bullet*>* getBullets();
	std::vector<Shield*>* getShields();
	std::vector<Generator*>* getGenerators();
};

#endif //GAME_CLIENT_GAMESTATE_H
