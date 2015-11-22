//
// Created by austin4e on 11/22/15.
//

#include "Powerup.h"

Powerup::Powerup(int x, int y, int type, int radius)
{
    this->x = x;
    this->y = y;                        //coordinates on game board
    this->type = type;                  //type of powerup
    this->radius = radius;              //size of powerup on the field
}