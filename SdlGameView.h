//
// Created by austin4e on 10/10/15.
//

#ifndef GAME_CLIENT_SDLGAMEVIEW_H
#define GAME_CLIENT_SDLGAMEVIEW_H

#include <iostream>
#include <vector>
#include <string.h>
//#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL2/SDL.h>
#include "SdlGameViewAdapter.h"
#include "SdlInputAdapter.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#define __gl_h_
#else
#include <GL/glut.h>
#endif

class SdlGameView{
private:
    SDL_Window* window;
    SDL_GLContext context;
    SdlInputAdapter* inputAdapter;
    SdlGameViewAdapter* gameViewAdapter;
    GLfloat sqr[4][2] = { {0.5f, 0.5f }, { -0.5f, 0.5f }, { -0.5f, -0.5f }, { 0.5f, -0.5f } };
    GLfloat tri[3][2] = { {0.5f, -0.5f }, { -0.5f, -0.5f }, { 0.0f, 0.5f } };
    char strPowerup[32];
    char strHealth[32];
    GLfloat highlight;
    GLfloat delta;  // used with highlight to create a "pulsate" effect with highlighting
public:
    SdlGameView(SdlGameViewAdapter* gva, SdlInputAdapter* ia);
    int init();
    int initGL();
    void exit();
    void drawSquare();
    void drawTriangle();
    void drawVehicle(Vehicle* vehicle);
    void pointToVehicle(Vehicle *vehicle);
    void drawBase(Base* base);
    void drawShield(Shield* shield);
    void drawGenerator(Generator* generator);
    void drawBullet(Bullet* bullet);
    void drawPowerup(Powerup* powerup);
    void drawHealthBar(int curHealth, int maxHealth, float x, float y);
    void drawHUD(Vehicle* client);
    int drawView();
};

#endif //GAME_CLIENT_SDLGAMEVIEW_H
