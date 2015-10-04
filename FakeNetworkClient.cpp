//
// Created by austin4e on 10/3/15.
//

/************************************
 *
 * TODO: ERASE THIS WHEN REAL NETWORK CLIENT IS WORKING
 * THIS IS MERELY TO TEST UPDATING THE GAMESTATE
 *
 * **********************************/

#include <stdio.h>
#include "FakeNetworkClient.h"
GameState FakeNetworkClient::getState(){
    return updateState();
}

GameState FakeNetworkClient::updateState(){
    state = nextState();
    return state;
}

GameState FakeNetworkClient::nextState(){
    GameState next;
    Vehicle *test = new Vehicle(x, y, 100, 0, 0);
    next.addPlayers(test);
    printf("x: %d y: %d\n", x, y);

    state.addPlayers(test);
    if(x < 200 && y == 50){
        x++;
    }
    if(x == 200 && y < 200){
        y++;
    }
    if(x > 50 && y == 200){
        x--;
    }if(x == 50 && y > 50){
        y--;
    }
    printf("new x: %d new y: %d\n", x, y);
    return next;
}