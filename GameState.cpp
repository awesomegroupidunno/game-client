//
// Created by austin4e on 9/20/15.
//
#include "Vehicle.h"
#include <iostream>
#include <vector>

class GameState{
    std::vector<Vehicle*> players;
public:
    void addPlayers(Vehicle* add){
        players.push_back(add);
    }
    std::vector<Vehicle*> getPlayers(){
        return players;
    }
    //TODO: populate GameState with containers (powerups, XP zone location, bases, etc.)
};