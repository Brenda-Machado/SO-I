#include "Enemy.h"

Enemy::Enemy(Point _pos, Vector _spe, std::list<Laser> *lasers)
{
    _row = 0;
    _col = 0;
    _size = 30;
    _alive = true;
    _position = _pos;
    _speed = _spe;
    _lasers = lasers;
}

bool Enemy::in_bound()
{
    if ((_position.x < 0) ||
        (_position.y > 600) ||
        (_position.y < 0))
        return false;
    return true;
}
bool Enemy::on_screen()
{
    if ((_position.x > 800) ||
        (_position.x < 0) ||
        (_position.y > 600) ||
        (_position.y < 0))
        return false;
    return true;
}

void Enemy::shoot()
{
    std::cout << "enemy shooted\n";
    Laser laser1 = Laser(_position, al_map_rgb(255, 0, 255), Vector(-420, -420));
    Laser laser2 = Laser(_position, al_map_rgb(255, 0, 255), Vector(-420, 420));
    Laser laser3 = Laser(_position, al_map_rgb(255, 0, 255), Vector(-600, 0));
    _lasers->push_back(laser1);
    _lasers->push_back(laser2);
    _lasers->push_back(laser3);
}