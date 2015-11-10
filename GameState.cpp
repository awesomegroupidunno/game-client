#include "GameState.h"

GameState::GameState()
{
	this->players = new std::vector<Vehicle*>();
	this->bases = new std::vector<Base*>();
	this->bullets = new std::vector<Bullet*>();
	this->shields = new std::vector<Shield*>();
	this->generators = new std::vector<Generator*>();
}
/*
 * add objects to the GameState
 */
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

void GameState::addShield(Shield *add)
{
	shields->push_back(add);
}

void GameState::addGenerator(Generator *add)
{
	generators->push_back(add);
}
/*
 * pass objects from the GameState
 */
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

std::vector<Shield*>* GameState::getShields()
{
	return shields;
}

std::vector<Generator*>* GameState::getGenerators()
{
	return generators;
}