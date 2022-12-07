#include "Laser.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>

Laser::Laser(Point cent, ALLEGRO_COLOR clr, Vector spe)
{
    centre = cent;
    speed = spe;
    active = true;
    color = clr;
    // centre = centre + speed * 0.1;
}
void Laser::update_pos(float dt)
{
    centre = centre + speed * dt;
    if (!in_bound())
        active = false;
}
bool Laser::in_bound()
{
    if ((centre.x > 800) ||
        (centre.x < 0) ||
        (centre.y > 600) ||
        (centre.y < 0))
        return false;
    return true;
}