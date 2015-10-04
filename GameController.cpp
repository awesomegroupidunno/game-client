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
