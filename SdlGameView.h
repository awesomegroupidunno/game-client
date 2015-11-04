//
// Created by austin4e on 10/10/15.
//

#ifndef GAME_CLIENT_SDLGAMEVIEW_H
#define GAME_CLIENT_SDLGAMEVIEW_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL2/SDL.h>
#include "SdlGameViewAdapter.h"
#include "SdlInputAdapter.h"

class SdlGameView{
private:
    SDL_Window* window;
    SDL_GLContext context;
    SdlInputAdapter* inputAdapter;
    SdlGameViewAdapter* gameViewAdapter;
    GLfloat sqr[4][2] = { {0.5f, 0.5f }, { -0.5f, 0.5f }, { -0.5f, -0.5f }, { 0.5f, -0.5f } };
public:
    SdlGameView(SdlGameViewAdapter* gva, SdlInputAdapter* ia);
    int init();
    int initGL();
    void exit();
    void drawSquare();
    void drawVehicle(SDL_Rect* vehicle, double angle, int teamColor);
    void drawBase(SDL_Rect* base, int teamColor);
    void drawBullet(SDL_Rect* bullet);
    int drawView();
};

#endif //GAME_CLIENT_SDLGAMEVIEW_H
