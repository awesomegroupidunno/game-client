//
// Created by austin4e on 9/20/15.
//

#ifndef GAME_CLIENT_VEHICLE_H
#define GAME_CLIENT_VEHICLE_H


class Vehicle{
public:
    int x, y;               //coordinates on game board
    double velocity, frontAngle;      //current angle the vehicle is facing
    int endurance;          //vehicle health
    //constants
    //double ACCEL_RATE = 1.0;     //acceleration rate -- placeholder value
    //double DECEL_RATE = 0.5;     //deceleration rate -- placeholder value
    //TODO: methods to handle movement, turning, speeding up, braking, etc.
    Vehicle(int cX, int cY, int end, double ang, double vel);
};


#endif //GAME_CLIENT_VEHICLE_H
