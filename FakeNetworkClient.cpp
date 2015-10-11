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
FakeNetworkClient::FakeNetworkClient(){
    x = 50;
    y = 50;
    angle = 180;
}

GameState FakeNetworkClient::updateState(){
    state = nextState();
    return state;
}

GameState FakeNetworkClient::getState(){
    return updateState();
}

GameState FakeNetworkClient::nextState(){
    GameState next;
    printf("%d\n", angle);
    printf("x:%d y:%d\n", x, y);
    Vehicle *test = new Vehicle(x, y, 100, angle, 0);
    next.addPlayers(test);
    return next;
}
// calculates movement based on trig and front-facing angle of player vehicle
void FakeNetworkClient::move(int direction) {
    double radian = angle*(M_PI/180);
    double reverseRadian = angle+180;
    if(reverseRadian > 359){
        reverseRadian -= 360;
    }
    reverseRadian *= (M_PI/180);
    double trueX = 2*cos(radian);
    double trueY = 2*sin(radian);
    if (direction == 1) { //move forward
        x += trueX;
        y -= trueY;
    } else if (direction == -1) { //move reverse
        trueX = 2*cos(reverseRadian);
        trueY = 2*sin(reverseRadian);
        x += trueX;
        y -= trueY;
    }
}
// turns vehicle angle, 8-axis movement for now, 45degree angles
void FakeNetworkClient::turn(int direction) {
    if(direction > 0) {
        angle += 45;
    }else{
        angle -= 45;
    }
    if(angle > 315){
        angle = 0;
    }
    if(angle < 0){
        angle = 315;
    }
}