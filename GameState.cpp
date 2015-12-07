#include "GameState.h"

GameState::GameState()
{
	this->players = new std::vector<Vehicle*>();
	this->bases = new std::vector<Base*>();
	this->bullets = new std::vector<Bullet*>();
	this->shields = new std::vector<Shield*>();
	this->generators = new std::vector<Generator*>();
	this->powerups = new std::vector<Powerup*>();
	this->rockets = new std::vector<Rocket*>();
	this->gravityWells = new std::vector<GravityWell*>();
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

void GameState::addPowerup(Powerup *add)
{
	powerups->push_back(add);
}

void GameState::addRocket(Rocket *add)
{
	rockets->push_back(add);
}

void GameState::addGravityWell(GravityWell *add)
{
	gravityWells->push_back(add);
}

void GameState::setGameOver(int gameOver)
{
	this->gameOver = gameOver;
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

std::vector<Powerup*>* GameState::getPowerups()
{
	return powerups;
}

std::vector<Rocket*>* GameState::getRockets()
{
	return rockets;
}

std::vector<GravityWell*>* GameState::getGravityWells()
{
	return gravityWells;
}

int GameState::getGameOver()
{
	return gameOver;
}