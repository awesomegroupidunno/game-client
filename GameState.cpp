#include "GameState.h"

void GameState::addPlayer(Vehicle* add)
{
	players.push_back(add);
}

std::vector<Vehicle*> GameState::getPlayers()
{
	return players;
}