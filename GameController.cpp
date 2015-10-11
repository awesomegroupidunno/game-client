//
// Created by Austin Forry on 9/14/15.
//

#include "GameController.h"
#include "Vehicle.h"
#include <iostream>
#include <vector>

/*
 * HANDLE GAME LOGIC AND PASSING GAMESTATE
 */
//constructor
std::vector<Vehicle*> GameController::getVehicles(){
    state = replaceState(state);
    return state.getPlayers();
}
GameState GameController::replaceState(GameState update){
    //TODO: get updated gamestate from serverside
    //networkClient is currently a FAKE Network Client
    //networkClient should be replaced by the real network client when it's working
    return networkClient.getState();
}
// passes call to move vehicle to network client
void GameController::moveVehicle(int direction){
    networkClient.move(direction);
}
// passes call to turn vehicle to network client
void GameController::turnVehicle(int direction){
    networkClient.turn(direction);
}
