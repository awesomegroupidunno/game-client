#ifndef GAME_CLIENT_GAMESTATE_H
#define GAME_CLIENT_GAMESTATE_H

#include "Vehicle.h"
#include "Base.h"
#include "Bullet.h"
#include "Shield.h"
#include "Generator.h"
#include "Powerup.h"
#include "Rocket.h"
#include "GravityWell.h"
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
	std::vector<Rocket*>* rockets;
	std::vector<GravityWell*>* gravityWells;

	int gameOver;
	int secToRestart;
public:
	GameState();
	void addPlayer(Vehicle* add);
	void addBase(Base* add);
	void addBullet(Bullet* add);
	void addShield(Shield* add);
	void addGenerator(Generator* add);
	void addPowerup(Powerup* add);
	void addRocket(Rocket* add);
	void addGravityWell(GravityWell* add);
	void setGameOver(int gameOver);
	void setSecToRestart(int secToRestart);

	std::vector<Vehicle*>* getPlayers();
	std::vector<Base*>* getBases();
	std::vector<Bullet*>* getBullets();
	std::vector<Shield*>* getShields();
	std::vector<Generator*>* getGenerators();
	std::vector<Powerup*>* getPowerups();
	std::vector<Rocket*>* getRockets();
	std::vector<GravityWell*>* getGravityWells();
	int getGameOver();
	int getSecToRestart();
};

#endif //GAME_CLIENT_GAMESTATE_H
