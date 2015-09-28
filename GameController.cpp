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
    //TODO: Replace getState with replaceState when replaceState is connected to serverside
    state = getState();
    return state.getPlayers();
}
GameState GameController::replaceState(GameState update){
    //TODO: get updated gamestate from serverside
    state = update;
    return state;
}
//TODO: GetState TESTS FOR DRAWING GAME, SERVER HANDLES WILL NEGATE THIS LATER
GameState GameController::getState(){
    Vehicle* test = new Vehicle(50,50,100,0,0);
    Vehicle* test2 = new Vehicle(200, 200, 100, 0, 0);
    state.addPlayers(test);
	state.addPlayers(test2);
    return state;
}
