//
// Created by Austin Forry on 9/14/15.
//

#ifndef GAME_CLIENT_GAMECONTROLLER_H
#define GAME_CLIENT_GAMECONTROLLER_H

#include "Vehicle.h"
#include "GameState.cpp"
#include <iostream>
#include <vector>

class GameController {
    //TODO: List methods to be used in GameController.cpp
    //TODO: methods to handle player input will be containers for vehicle methods
    //TODO: GameController will not actually handle input, but instead be called from
    //TODO: a separate InputAdapter class
    GameState state;
public:
    std::vector<Vehicle*> getVehicles();
    void replaceGameState(GameState replace);
};


#endif //GAME_CLIENT_GAMECONTROLLER_H
