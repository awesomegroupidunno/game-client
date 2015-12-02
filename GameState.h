#ifndef GAME_CLIENT_GAMESTATE_H
#define GAME_CLIENT_GAMESTATE_H

#include "Vehicle.h"
#include "Base.h"
#include "Bullet.h"
#include "Shield.h"
#include "Generator.h"
#include "Powerup.h"
#include <iostream>
#include <vector>

#define RED_TEAM 0
#define BLUE_TEAM 1

class GameState
{
private:
	std::vector<Vehicle*>* players;
	std::vector<Base*>* bases;
	std::vector<Bullet*>* bullets;
	std::vector<Shield*>* shields;
	std::vector<Generator*>* generators;
	std::vector<Powerup*>* powerups;
	int gameOver;
public:
	GameState();
	void addPlayer(Vehicle* add);
	void addBase(Base* add);
	void addBullet(Bullet* add);
	void addShield(Shield* add);
	void addGenerator(Generator* add);
	void addPowerup(Powerup* add);
	void setGameOver(int gameOver);
	std::vector<Vehicle*>* getPlayers();
	std::vector<Base*>* getBases();
	std::vector<Bullet*>* getBullets();
	std::vector<Shield*>* getShields();
	std::vector<Generator*>* getGenerators();
	std::vector<Powerup*>* getPowerups();
	int getGameOver();
};

#endif //GAME_CLIENT_GAMESTATE_H
