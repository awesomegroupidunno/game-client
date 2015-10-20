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
#include "GameState.h"
#include "Vehicle.h"

class FakeNetworkClient {
private:
    int x;
    int y;
    int angle;
    GameState state;
public:
    FakeNetworkClient();
    GameState getState();
    GameState updateState();
    GameState nextState();
    void move(int direction);
    void turn(int direction);
};


#endif //GAME_CLIENT_FAKENETWORKCLIENT_H
