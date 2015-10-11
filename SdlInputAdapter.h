//
// Created by austin4e on 10/10/15.
//

#ifndef GAME_CLIENT_SDLINPUTADAPTER_H
#define GAME_CLIENT_SDLINPUTADAPTER_H

#include "SDL2/SDL.h"
#include "GameController.h"

class SdlInputAdapter {
private:
    GameController* gameController;
public:
    SdlInputAdapter(GameController* gc);
    void inputListener(SDL_Event event);
};


#endif //GAME_CLIENT_SDLINPUTADAPTER_H
