//
// Created by austin4e on 10/31/15.
//

#include "Base.h"

//constructor
Base::Base(int x, int y, int curHealth, int team, int width, int height){
    this->x = x;
    this->y = y;                        //coordinates on game board
    this->curHealth = curHealth;        //base health
    this->team = team;                  //base team ID (0 = red, 1 = blue)
    this->width = width;
    this->height = height;              //base width and height
}