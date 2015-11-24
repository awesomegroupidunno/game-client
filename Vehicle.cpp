//
// Created by austin4e on 9/20/15.
//
#include "Vehicle.h"

//constructor
Vehicle::Vehicle(int x, int y, int curHealth, int maxHealth, int frontAngle, int team, int width,
                 int height, bool isMe)
{
    this->x = x;
    this->y = y;                        //coordinates on game board
    this->frontAngle = frontAngle;      //current angle the vehicle is facing
    this->curHealth = curHealth;        //vehicle health
    this->maxHealth = maxHealth;
    this->team = team;                  //vehicle team ID (0 = red, 1 = blue)
    this->width = width;
    this->height = height;              //vehicle width and height
    this->isMe = isMe;                  //tells client which vehicle is its vehicle
    //TODO: possibly include powerup classes / objects
}