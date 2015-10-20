//
// Created by Austin Forry on 9/14/15.
//

#include "GameController.h"

/*
 * HANDLE GAME LOGIC AND PASSING GAMESTATE
 */

// Constructor
GameController::GameController(GameState* state, NetworkClient* client)
{
	this->state = state;
	this->client = client;
	client->set_controller(this);
}

void GameController::update(GameState* new_state)
{
	delete state;
	state = new_state;
}

std::vector<Vehicle*>* GameController::getVehicles(){
    return state->getPlayers();
}

// passes call to move vehicle to network client
void GameController::moveVehicle(int direction)
{
    client->move_command(direction);
}

// passes call to turn vehicle to network client
void GameController::turnVehicle(int direction)
{
    client->turn_command(direction);
}
