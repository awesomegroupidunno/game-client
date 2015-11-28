//
// Created by austin4e on 9/20/15.
//

#ifndef GAME_CLIENT_VEHICLE_H
#define GAME_CLIENT_VEHICLE_H


class Vehicle{
public:
    // TODO: fields for storing a powerup a vehicle has collected
    int x, y, curHealth, maxHealth, team, width, height, frontAngle, storedPower, activePowerup;
    bool isMe;
    Vehicle(int x, int y, int curHealth, int maxHealth, int frontAngle, int team, int width,
			int height, int storedPowerup, int activePowerup, bool isMe);
};


#endif //GAME_CLIENT_VEHICLE_H
