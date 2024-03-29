/**
 * @file Missile.h
 * @brief Shoot by the boss
 *
 * @author
 * @bug
 */

#ifndef MISSILE_H
#define MISSILE_H

#include <allegro5/allegro.h>
#include <memory>

#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "thread.h"
#include <list>

__USING_API

class Missile
{
public:
    Missile(Point pos, Vector spe);
    void update_pos(float dt);
    bool in_bound();

public:
    Point _position;
    Vector _speed;
    int an_frm; // animation frame
    bool active;
    float _angle;
};

#endif