#include "Enemy.h"

void Enemy::spawn()
{
    _alive = true;
    _sprite = NULL;
}

void Enemy::update(float dt)
{
    if (isAlive())
    {
        _position = _speed * dt;
    } 
}
