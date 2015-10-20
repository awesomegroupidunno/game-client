//
// Created by Austin Forry on 9/14/15.
//

#ifndef GAME_CLIENT_GAMECONTROLLER_H
#define GAME_CLIENT_GAMECONTROLLER_H

#include "Vehicle.h"
#include <iostream>
#include <vector>
#include "NetworkClient.h"

class NetworkClient;

class GameController {
    //TODO: List methods to be used in GameController.cpp
    //methods to handle player input will be containers for vehicle methods
    //GameController will not actually handle input, but instead be called from
    //a separate InputAdapter class
    GameState* state;
    NetworkClient* client;

public:
	GameController(GameState* state, NetworkClient* client);

	void update(GameState* new_state);
    std::vector<Vehicle*>* getVehicles();
    void moveVehicle(int direction);
    void turnVehicle(int direction);
};


#endif //GAME_CLIENT_GAMECONTROLLER_H
