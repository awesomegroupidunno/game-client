//
// Created by austin4e on 9/20/15.
//
#include "Vehicle.h"

//constructor
Vehicle::Vehicle(int x, int y, int curHealth, double frontAngle, double velocity, int team, int width, int height){
    this->velocity = velocity;          //current velocity
    this->x = x;
    this->y = y;                        //coordinates on game board
    this->frontAngle = frontAngle;      //current angle the vehicle is facing
    this->curHealth = curHealth;        //vehicle health
    this->team = team;                  //vehicle team ID (0 = red, 1 = blue)
    this->width = width;
    this->height = height;              //vehicle width and height
    //TODO: possibly include powerup classes / objects
}