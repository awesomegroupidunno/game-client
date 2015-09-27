//
// Created by austin4e on 9/26/15.
//

#include "GameController.h"
#include "SdlGameViewAdapter.h"
#include <iostream>
#include <vector>

/*
 * communications between SdlGameView and GameController
 */

std::vector<Vehicle*> SdlGameViewAdapter::getVehicles(){
    GameController gc;
    return gc.getVehicles();
}