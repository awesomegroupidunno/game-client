//
// Created by Austin Forry on 9/14/15.
//

#ifndef GAME_CLIENT_GAMECONTROLLER_H
#define GAME_CLIENT_GAMECONTROLLER_H

#include "Vehicle.h"
//#include "GameState.cpp"
#include "FakeNetworkClient.h"
#include <iostream>
#include <vector>

class GameController {
    //TODO: List methods to be used in GameController.cpp
    //methods to handle player input will be containers for vehicle methods
    //GameController will not actually handle input, but instead be called from
    //a separate InputAdapter class
    GameState state;
    //TODO: REPLACE WITH REAL NETWORK CLIENT LATER
    FakeNetworkClient networkClient;
public:
    std::vector<Vehicle*> getVehicles();
    GameState replaceState(GameState update);
    void moveVehicle(int direction);
    void turnVehicle(int direction);
};


#endif //GAME_CLIENT_GAMECONTROLLER_H
