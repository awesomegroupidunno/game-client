//
// Created by Austin Forry on 9/14/15.
//

#ifndef GAME_CLIENT_GAMECONTROLLER_H
#define GAME_CLIENT_GAMECONTROLLER_H

//#include "Vehicle.h"
//#include "Base.h"
#include <iostream>
#include <vector>
#include "NetworkClient.h"

class NetworkClient;

class GameController {
private:
    GameState* state;
    NetworkClient* client;
    pthread_mutex_t* game_state_mutex;

public:
	GameController(GameState* state, NetworkClient* client, pthread_mutex_t* game_state_mutex);

	void update(GameState* new_state);
    std::vector<Vehicle*>* getVehicles();
    std::vector<Base*>* getBases();
	std::vector<Bullet*>* getBullets();
    std::vector<Shield*>* getShields();
    std::vector<Generator*>* getGenerators();
    std::vector<Powerup*>* getPowerups();
    std::vector<Rocket*>* getRockets();
    std::vector<GravityWell*>* getGravityWells();
	int getGameOver();

    // Respond to input
    void moveVehicle(double direction);
    void turnVehicle(double direction);
	void fireWeapon();
	void activatePowerup();
};


#endif //GAME_CLIENT_GAMECONTROLLER_H
