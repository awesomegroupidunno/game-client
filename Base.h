//
// Created by austin4e on 10/31/15.
//

#ifndef GAME_CLIENT_BASE_H
#define GAME_CLIENT_BASE_H


class Base {
public:
    int x, y, curHealth, maxHealth, team, width, height;    //coordinates on game board, health, team color
    Base(int x, int y, int curHealth, int maxHealth, int team, int width, int height);
};


#endif //GAME_CLIENT_BASE_H
