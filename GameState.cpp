#include "GameState.h"

GameState::GameState()
{
	this->players = new std::vector<Vehicle*>();
	this->bases = new std::vector<Base*>();
}

void GameState::addPlayer(Vehicle* add)
{
	players->push_back(add);
}

void GameState::addBase(Base* add)
{
	bases->push_back(add);
}

std::vector<Vehicle*>* GameState::getPlayers()
{
	return players;
}

std::vector<Base*>* GameState::getBases()
{
	return bases;
}