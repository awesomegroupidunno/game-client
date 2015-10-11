//
// Created by austin4e on 9/20/15.
//

#ifndef GAME_CLIENT_VEHICLE_H
#define GAME_CLIENT_VEHICLE_H


class Vehicle{
public:
    int x, y, frontAngle, endurance;    //coordinates on game board, front facing angle, health
    double velocity;                    //current angle the vehicle is facing
    Vehicle(int cX, int cY, int end, int ang, double vel);
};


#endif //GAME_CLIENT_VEHICLE_H
