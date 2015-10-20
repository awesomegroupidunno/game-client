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