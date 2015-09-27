//
// Created by Austin Forry on 9/14/15.
//

#include "GameController.h"
#include "Vehicle.h"
#include "GameState.cpp"
#include <iostream>
#include <vector>

/*
 * TODO: HANDLE GAME LOGIC
 */
//constructor
std::vector<Vehicle*> GameController::getVehicles(){
    return state.getPlayers();
}
void GameController::replaceGameState(GameState replace){
    state = replace;
}
