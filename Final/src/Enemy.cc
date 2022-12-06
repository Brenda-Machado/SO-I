#include "Enemy.h"

__BEGIN_API


void Enemy::spawn()
{
    _alive = true;
    _sprite = NULL;
}

void Enemy::update(float dt)
{
    if (isAlive())
    {
        // Update sprite
    } 
}

void Enemy::move()
{
    // Move the enemy
}

__END_API