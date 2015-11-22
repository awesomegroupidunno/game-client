//
// Created by austin4e on 11/22/15.
//

#ifndef GAME_CLIENT_POWERUP_H
#define GAME_CLIENT_POWERUP_H


class Powerup {
public:
    int x, y, type, radius;    //coordinates on game board, health, team color
    Powerup(int x, int y, int type, int radius);
};


#endif //GAME_CLIENT_POWERUP_H
