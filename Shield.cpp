//
// Created by austin4e on 11/8/15.
//

#include "Shield.h"
/*
 * Shields will surround bases and protect them.

 * Shields do NOT have a health field.
 *
 * Instead shields will exist until their
 * corresponding generator reaches a health of zero.
 *
 * Shields and generators will be paired according
 * to their team int.
 */
Shield::Shield(int x, int y, int team, int width, int height, bool isEnabled) {
    this->x = x;
    this->y = y;
    this->team = team;
    this->width = width;
    this->height = height;
    this->isEnabled = isEnabled;
}
