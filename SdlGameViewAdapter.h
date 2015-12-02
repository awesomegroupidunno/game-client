//
// Created by austin4e on 9/26/15.
//

#ifndef GAME_CLIENT_SDLGAMEVIEWADAPTER_H
#define GAME_CLIENT_SDLGAMEVIEWADAPTER_H

//#include "Vehicle.h"
//#include "Base.h"
#include "GameController.h"
#include <iostream>
#include <vector>

class SdlGameViewAdapter{
    GameController* gameController;
public:
    SdlGameViewAdapter(GameController* gc);
    std::vector<Vehicle*>* getVehicles();
    std::vector<Base*>* getBases();
    std::vector<Bullet*>* getBullets();
    std::vector<Shield*>* getShields();
    std::vector<Generator*>* getGenerators();
    std::vector<Powerup*>* getPowerups();
	int getGameOver();
};

#endif //GAME_CLIENT_SDLGAMEVIEWADAPTER_H
