//
// Created by austin4e on 10/31/15.
//

#include "Base.h"

Base::Base(int x, int y, int curHealth, int maxHealth, int team, int width, int height)
{
    this->x = x;
    this->y = y;                        //coordinates on game board
    this->curHealth = curHealth;        //base health
    this->maxHealth = maxHealth;
    this->team = team;                  //base team ID (0 = red, 1 = blue)
    this->width = width;
    this->height = height;              //base width and height
}