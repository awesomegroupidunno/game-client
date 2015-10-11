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
#include <math.h>
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
    Vehicle *test = new Vehicle(x, y, 100, angle, 0);
    next.addPlayers(test);
    printf("vehicle angle: %d\nVehicle X and Y: %d, %d\n", angle, x, y);
    return next;
}
void FakeNetworkClient::move(int direction) {
    if (direction == 1) { //move forward
        x = cos(angle);
        y = sin(angle);
    } else if (direction == -1) { //move reverse
        int reverseAng = angle;
        for(int i = 0; i < 180; i++){
            reverseAng++;
            if(reverseAng == 360){
                reverseAng = 0;
            }
        }
        x = cos(reverseAng);
        y = sin(reverseAng);
    }
}
void FakeNetworkClient::turn(int direction) {
    angle += direction; //+1 for left (counterclockwise) -1 for right (clockwise)
    if(angle == 360){
        angle = 0;
    }if(angle == -1){
        angle = 359;
    }
}