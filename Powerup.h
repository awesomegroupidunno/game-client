//
// Created by austin4e on 11/22/15.
//

#ifndef GAME_CLIENT_POWERUP_H
#define GAME_CLIENT_POWERUP_H

// The different types of powerups (P for powerup)
#define P_ROCKET       	0
#define P_HEALTH_UP     1

class Powerup {
public:
    int x, y, type, radius;    //coordinates on game board, health, team color
    Powerup(int x, int y, int type, int radius);
};


#endif //GAME_CLIENT_POWERUP_H
