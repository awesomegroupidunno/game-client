//
// Created by Austin Forry on 9/14/15.
//

#ifndef GAME_CLIENT_GAMECONTROLLER_H
#define GAME_CLIENT_GAMECONTROLLER_H

#include "Vehicle.h"
#include "Base.h"
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
    //GameController will not handle input, but instead be called from
    //a separate InputAdapter class
    void moveVehicle(double direction);
    void turnVehicle(double direction);
};


#endif //GAME_CLIENT_GAMECONTROLLER_H
