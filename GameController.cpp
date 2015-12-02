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

std::vector<Bullet*>* GameController::getBullets()
{
	std::vector<Bullet*>* bullets;

	pthread_mutex_lock(game_state_mutex);
	bullets = state->getBullets();
	pthread_mutex_unlock(game_state_mutex);

	return bullets;
}

std::vector<Shield*> *GameController::getShields() {
	std::vector<Shield*>* shields;

	pthread_mutex_lock(game_state_mutex);
	shields = state->getShields();
	pthread_mutex_unlock(game_state_mutex);

	return shields;
}

std::vector<Generator*> *GameController::getGenerators() {
	std::vector<Generator*>* gens;

	pthread_mutex_lock(game_state_mutex);
	gens = state->getGenerators();
	pthread_mutex_unlock(game_state_mutex);

	return gens;
}

std::vector<Powerup*> *GameController::getPowerups() {
	std::vector<Powerup*>* powerups;

	pthread_mutex_lock(game_state_mutex);
	powerups = state->getPowerups();
	pthread_mutex_unlock(game_state_mutex);

	return powerups;
}

int GameController::getGameOver()
{
	int gameOver;

	pthread_mutex_lock(game_state_mutex);
	gameOver = state->getGameOver();
	pthread_mutex_unlock(game_state_mutex);

	return gameOver;
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
// passes call to activate powerup to network client
void GameController::activatePowerup()
{
	client->activate_powerup_command();
}
