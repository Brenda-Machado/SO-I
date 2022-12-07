/**
 * @file Mine.h
 * @brief Projectile spawned every 30 seconds
 *
 * @author
 * @bug
 */

#ifndef MINE_H
#define MINE_H

#include <allegro5/allegro.h>
#include <memory>

#include "Point.h"
#include "Vector.h"
#include "Laser.h"
#include "Sprite.h"
#include "thread.h"
#include <list>
__USING_API

class Mine
{
public:
    Mine(Point cent, Vector spe, std::list<Laser> *lsr);
    void update_pos(float dt);
    void explode();
    static void start(std::list<Mine> *mines, std::list<Laser> *lasers);
    static void end();

public:
    Point centre;
    Vector speed;
    ALLEGRO_COLOR color;
    int col;
    int row;
    std::list<Laser> *lasers;
    float creation_time;
    int size;

private:
    static bool _finish;
};

#endif
