//
// Created by austin4e on 11/8/15.
//

#ifndef GAME_CLIENT_SHIELD_H
#define GAME_CLIENT_SHIELD_H


class Shield {
public:
    int x, y, team, width, height;    //coordinates on game board, team color, etc
    bool isEnabled;
    Shield(int x, int y, int team, int width, int height, bool isEnabled);
};


#endif //GAME_CLIENT_SHIELD_H
