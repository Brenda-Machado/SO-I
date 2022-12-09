#include "Missile.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>

Missile::Missile(Point pos, Vector spe)
{
    _position = pos;
    _speed = spe;
    active = true;
    an_frm = 0;
}
void Missile::update_pos(float dt)
{
    _position = _position + _speed * dt;
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