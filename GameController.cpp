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
    //state = getState();
    state = replaceState(state);
    return state.getPlayers();
}
GameState GameController::replaceState(GameState update){
    //TODO: get updated gamestate from serverside
    return networkClient.getState();
}
//TODO: GetState TESTS FOR DRAWING GAME, SERVER HANDLES WILL NEGATE THIS LATER, CAN BE DELETED
/*GameState GameController::getState(){
    Vehicle* test = new Vehicle(x,50,100,0,0);
    Vehicle* test2 = new Vehicle(200, 200, 100, 0, 0);
    x++;
    state.addPlayers(test);
	state.addPlayers(test2);
    return state;
}*/
