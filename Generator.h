//
// Created by austin4e on 11/8/15.
//

#ifndef GAME_CLIENT_GENERATOR_H
#define GAME_CLIENT_GENERATOR_H


class Generator {
public:
    int x, y, curHealth, maxHealth, team, width, height;    //coordinates on game board, health, team color
    Generator(int x, int y, int curHealth, int team, int width, int height);
};


#endif //GAME_CLIENT_GENERATOR_H
