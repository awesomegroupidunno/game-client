//
// Created by austin4e on 11/22/15.
//

#ifndef GAME_CLIENT_POWERUP_H
#define GAME_CLIENT_POWERUP_H

// The different types of powerups (P for powerup)
#define NO_POWERUP -1
#define HEAL 1
#define SPEEDUP 2
#define ROCKET 3
#define GRAVWELL 4

class Powerup {
public:
    int x, y, type, width, height;    //coordinates on game board, health, team color
    Powerup(int x, int y, int type, int width, int height);
};


#endif //GAME_CLIENT_POWERUP_H
