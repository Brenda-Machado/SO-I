/**
 * @file Enemy.h
 * @brief
 *
 * @author
 * @bug
 */
#include <allegro5/allegro.h>

#include "Vector.h"
#include "Point.h"
#include "thread.h"
#include "Sprite.h"

__BEGIN_API

class Enemy
{
    
public:
    Enemy(Point _position, Vector _speed, int _hp, int _damage, bool _alive) {};
    ~Enemy() {};
    
    Point getPosition() {
        return _position;
    };
    Vector getSpeed() {
        return _speed;
    };
    int getHp() {
        return _hp;
    };
    int getDamage() {
        return _damage;
    };
    bool isAlive() {
        return _alive;
    };
    Sprite* getSprite() {
        return _sprite;
    };
    inline int get_row() const
    {
        return _row;
    }
    inline int get_col() const
    {
        return _col;
    }

private:
    Point _position; // center of the enemy
    Vector _speed;
    int _hp;
    int _row;
    int _col;
    int _damage;
    bool _alive;
    
    Sprite *_sprite;
};

__END_API