//
// Created by austin4e on 10/3/15.
//

/************************************
 *
 * TODO: ERASE THIS WHEN REAL NETWORK CLIENT IS WORKING
 * THIS IS MERELY TO TEST UPDATING THE GAMESTATE
 *
 * **********************************/

#ifndef GAME_CLIENT_FAKENETWORKCLIENT_H
#define GAME_CLIENT_FAKENETWORKCLIENT_H
#include "GameState.cpp"
#include "Vehicle.h"

class FakeNetworkClient {
    int x = 50;
    int y = 50;
    double angle = 270.0;
    GameState state;
public:
    GameState getState();
    GameState updateState();
    GameState nextState();
    void move(int direction);
    void turn(int direction);
};


#endif //GAME_CLIENT_FAKENETWORKCLIENT_H
