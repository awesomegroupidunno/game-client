//
// Created by Austin Forry on 9/14/15.
//

#include "GameController.h"

/*
 * HANDLE GAME LOGIC AND PASSING GAMESTATE
 */

// Constructor
GameController::GameController(GameState* state, NetworkClient* client, pthread_mutex_t* game_state_mutex)
{
	this->state = state;
	this->client = client;
	this->game_state_mutex = game_state_mutex;
	client->set_controller(this);
}

void GameController::update(GameState* new_state)
{
	delete state;
	state = new_state;
}

std::vector<Vehicle*>* GameController::getVehicles()
{
	std::vector<Vehicle*>* vehicles;

	pthread_mutex_lock(game_state_mutex);
    vehicles = state->getPlayers();
	pthread_mutex_unlock(game_state_mutex);

	return vehicles;
}

std::vector<Base*>* GameController::getBases()
{
	std::vector<Base*>* bases;

	pthread_mutex_lock(game_state_mutex);
	bases = state->getBases();
	pthread_mutex_unlock(game_state_mutex);

	return bases;
}

// passes call to move vehicle to network client
void GameController::moveVehicle(double direction)
{
    client->move_command(direction);
}

// passes call to turn vehicle to network client
void GameController::turnVehicle(double direction)
{
    client->turn_command(direction);
}

// passes call to fire weapon to network client
void GameController::fireWeapon()
{
	client->fire_command();
}
