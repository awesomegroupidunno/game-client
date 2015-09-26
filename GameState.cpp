//
// Created by austin4e on 9/20/15.
//
#include "Vehicle.cpp"

class GameState{
    GameState();
    //constructor
    GameState::GameState(){
        //store values and objects needed to update GameState
        int numPlayers;                 //number of players in current session
        Vehicle players[numPlayers];    //array of each players vehicle
        //TODO: populate GameState with containers (powerups, XP zone location, bases, etc.)
    }
};