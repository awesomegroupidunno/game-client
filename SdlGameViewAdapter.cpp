//
// Created by austin4e on 9/26/15.
//

#include "SdlGameViewAdapter.h"
#include <iostream>
#include <vector>

/*
 * communications between SdlGameView and GameController
 */

std::vector<Vehicle*> SdlGameViewAdapter::getVehicles(){
    return gc.getVehicles();
}