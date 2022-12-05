/**
 * @file Laser.h
 * @brief derived class of Projectile
 *
 * @author
 * @bug
 */

#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h>

#include "Point.h"
#include "Vector.h"

class Laser
{
public:
    Laser(Point cent, ALLEGRO_COLOR clr, Vector spe);
    bool in_bound();
    void update_pos(float dt);

public:
    Point centre;
    Vector speed;
    bool active;
    ALLEGRO_COLOR color;
};

#endif
