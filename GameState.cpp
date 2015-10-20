#include "GameState.h"

GameState::GameState()
{
	this->players = new std::vector<Vehicle*>();
}

void GameState::addPlayer(Vehicle* add)
{
	players->push_back(add);
}

std::vector<Vehicle*>* GameState::getPlayers()
{
	return players;
}