//
// Created by austin4e on 10/10/15.
//

#ifndef GAME_CLIENT_SDLGAMEVIEW_H
#define GAME_CLIENT_SDLGAMEVIEW_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "SdlGameViewAdapter.h"
#include "SdlInputAdapter.h"

class SdlGameView{
private:
    SDL_Renderer* renderer;
    SdlInputAdapter* inputAdapter;
    SdlGameViewAdapter* gameViewAdapter;
    const int carWidth = 50;
    const int carHeight = 75;
public:
    SdlGameView(SdlGameViewAdapter* gva, SdlInputAdapter* ia);
    void drawVehicle(SDL_Rect* vehicle);
    int drawView();
};

#endif //GAME_CLIENT_SDLGAMEVIEW_H
