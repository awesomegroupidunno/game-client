//
// Created by austin4e on 9/20/15.
//

#ifndef GAME_CLIENT_VEHICLE_H
#define GAME_CLIENT_VEHICLE_H


class Vehicle{
public:
    int x, y, curHealth, maxHealth, team, width, height;    //coordinates on game board, front facing angle, health
    double frontAngle, velocity;                            //current angle the vehicle is , vehicle
    bool isMe;                                              //bool to tell client which vehicle belongs to it
    Vehicle(int x, int y, int curHealth, double frontAngle, double velocity, int team, int width, int height, bool isMe);
};


#endif //GAME_CLIENT_VEHICLE_H
