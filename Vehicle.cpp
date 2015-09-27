//
// Created by austin4e on 9/20/15.
//
#include "Vehicle.h"

//constructor
Vehicle::Vehicle(int cX, int cY, int end, double ang, double vel){
    //values will be passed to GameState
    //values are placeholders for testing purposes
    velocity = vel;        //current velocity
    x = cX;
    y = cY;               //coordinates on game board
    frontAngle = ang;      //current angle the vehicle is facing
    endurance = end;          //vehicle health
    //TODO: possibly include powerup classes / objects
}
//TODO: methods to handle movement, turning, speeding up, braking, etc.