#include "GameState.h"

GameState::GameState()
{
	this->players = new std::vector<Vehicle*>();
	this->bases = new std::vector<Base*>();
	this->bullets = new std::vector<Bullet*>();
}

void GameState::addPlayer(Vehicle* add)
{
	players->push_back(add);
}

void GameState::addBase(Base* add)
{
	bases->push_back(add);
}

void GameState::addBullet(Bullet *add)
{
	bullets->push_back(add);
}

std::vector<Vehicle*>* GameState::getPlayers()
{
	return players;
}

std::vector<Base*>* GameState::getBases()
{
	return bases;
}

std::vector<Bullet*>* GameState::getBullets()
{
	return bullets;
}