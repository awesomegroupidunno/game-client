//
// Created by austin4e on 9/20/15.
//

#ifndef GAME_CLIENT_VEHICLE_H
#define GAME_CLIENT_VEHICLE_H


class Vehicle{
public:
    int x, y, endurance;    //coordinates on game board, front facing angle, health
    double frontAngle, velocity;                    //current angle the vehicle is facing
    Vehicle(int cX, int cY, int end, double frontAngle, double vel);
};


#endif //GAME_CLIENT_VEHICLE_H
