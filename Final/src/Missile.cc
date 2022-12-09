#include "Missile.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>

Missile::Missile(Point pos, Vector spe)
{
    _position = pos;
    _speed = spe;
    active = true;
    an_frm = 0;
    _angle = atan(spe.y/spe.x)+4.71;
}
void Missile::update_pos(float dt)
{
    _position = _position + _speed * dt;
    an_frm++;
    if (an_frm > 7)
        an_frm = 0;
    if (!in_bound())
        active = false;
}
bool Missile::in_bound()
{
    if ((_position.x > 800) ||
        (_position.x < 0) ||
        (_position.y > 600) ||
        (_position.y < 0))
        return false;
    return true;
}