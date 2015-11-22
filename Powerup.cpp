//
// Created by austin4e on 11/22/15.
//

#include "Powerup.h"

Powerup::Powerup(int x, int y, int type, int width, int height)
{
    this->x = x;
    this->y = y;                        //coordinates on game board
    this->type = type;                  //type of powerup
    this->width = width;                //size of powerup on the field
    this->height = height;
}