//
// Created by austin4e on 11/8/15.
//

#include "Generator.h"

/*
 * Generators will correspond to a shield
 * based on their team ints.
 *
 * When the generator's current health is
 * lowered to zero, both the generator and
 * its corresponding shield are destroyed.
 */
Generator::Generator(int x, int y, int curHealth, int team, int width, int height) {
    this->x = x;
    this->y = y;
    this->curHealth = curHealth;
    this->team = team;
    this->width = width;
    this->height = height;
}
