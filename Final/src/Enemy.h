/**
 * @file Enemy.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>

#include "Vector.h"
#include "Point.h"

#include "thread.h"
#include "Sprite.h"

__BEGIN_API

class Enemy
{
    
public:
    Enemy();
    ~Enemy();
    
    void spawn();
    void update(double dt);
    
    void move();
    
    void setPosition(Point position);
    void setSpeed(Vector speed);
    void setHp(int hp);
    void setDamage(int damage);
    
    int getPosition();
    int getSpeed();
    int getHp();
    int getDamage();

    void setAlive(bool alive);
    bool isAlive();
    
    void setDirection(int direction);
    int getDirection();
    
    void setSprite(ALLEGRO_BITMAP *sprite);
    ALLEGRO_BITMAP *getSprite();

private:
    Point _position; // center of the enemy
    Vector _speed;
    int _hp;
    int _damage;
    bool _alive;
    int _direction;
    
    ALLEGRO_BITMAP *_sprite;
}
#endif

__END_API