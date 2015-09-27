//
// Created by Austin Forry on 9/14/15.
//

#include "GameController.h"
#include "Vehicle.h"
#include <iostream>
#include <vector>

/*
 * TODO: HANDLE GAME LOGIC
 */
//constructor
std::vector<Vehicle*> GameController::getVehicles(){
    state = getState();
    return state.getPlayers();
}
GameState GameController::replaceState(GameState update){
    state = update;
}
//TODO: TESTS FOR DRAWING GAME, SERVER HANDLES THE GAME STATE LATER
GameState GameController::getState(){
    Vehicle* test = new Vehicle(50,50,100,0,0);
    state.addPlayers(test);
    return state;
}
