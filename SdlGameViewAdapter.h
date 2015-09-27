//
// Created by austin4e on 9/26/15.
//

#ifndef GAME_CLIENT_SDLGAMEVIEWADAPTER_H
#define GAME_CLIENT_SDLGAMEVIEWADAPTER_H

#include "Vehicle.h"
#include <iostream>
#include <vector>

class SdlGameViewAdapter{
public:
    std::vector<Vehicle*> getVehicles();
};

#endif //GAME_CLIENT_SDLGAMEVIEWADAPTER_H
