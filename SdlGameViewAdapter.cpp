//
// Created by austin4e on 9/26/15.
//

#include "SdlGameViewAdapter.h"

/*
 * communications between SdlGameView and GameController
 */
SdlGameViewAdapter::SdlGameViewAdapter(GameController* gc) {
    gameController = gc;
}

std::vector<Vehicle*>* SdlGameViewAdapter::getVehicles(){
    return gameController->getVehicles();
}

std::vector<Base*>* SdlGameViewAdapter::getBases(){
    return gameController->getBases();
}

std::vector<Bullet*>* SdlGameViewAdapter::getBullets(){
    return gameController->getBullets();
}

std::vector<Shield*>* SdlGameViewAdapter::getShields(){
    return gameController->getShields();
}

std::vector<Generator*>* SdlGameViewAdapter::getGenerators(){
    return gameController->getGenerators();
}

std::vector<Powerup*>* SdlGameViewAdapter::getPowerups(){
    return gameController->getPowerups();
}