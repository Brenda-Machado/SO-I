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
#include "Laser.h"

#include <list>
#ifndef ENEMY_H
#define ENEMY_H
__USING_API

class Enemy
{
public:
    Enemy(Point _pos, Vector _spe, std::list<Laser> *lasers);
    Enemy(){};
    bool in_bound();
    bool on_screen();
    ~Enemy(){};
    virtual void shoot();

    Point getPosition() { return _position; };
    void setPosition(Point position) { _position = position; };
    void kill() { _alive = false; };
    Vector getSpeed() { return _speed; };
    bool isAlive() { return _alive; };
    inline int get_row() const { return _row; };
    inline int get_col() const { return _col; };
    int get_size() const { return _size; };

protected:
    Point _position; 
    Vector _speed;
    int _row;
    int _col;
    bool _alive;
    int _size;
    std::list<Laser> *_lasers;
};
#endif