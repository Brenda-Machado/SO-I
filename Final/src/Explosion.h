/**
 * @file Explosion.h
 * @brief
 *
 * @author
 * @bug
 */
#include <allegro5/allegro.h>

#include "Vector.h"
#include "Point.h"
#include "Sprite.h"

#ifndef EXPLOSION_H
#define EXPLOSION_H

__USING_API

class Explosion
{
public:
    Explosion(Point _pos, int frame)
    {
        _position = _pos;
        _frame = frame;
    };
    Explosion(){};
    ~Explosion(){};
    int getFrame() { return _frame; };
    Point getPosition() { return _position; };
    bool isFinished() { return _frame >= 5; };

    Point _position;
    int _frame;
};

#endif