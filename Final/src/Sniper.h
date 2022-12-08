/**
 * @file Sniper.h
 * @brief
 *
 * @author
 * @bug
 */
#include "Enemy.h"
#include "Ship.h"
#ifndef SNIPER_H
#define SNIPER_H
__USING_API

class Sniper : Enemy
{
public:
    static void start_controller(std::list<Laser> *lasers, std::list<Enemy> *enemies, Ship *ship);
    Sniper(Point _pos, Vector _spe, std::list<Laser> *lasers);
    void shoot() override;
    static void end() { _finish = true; };

private:
    static void spawn(std::list<Enemy> *enemies, std::list<Laser> *lasers);
    static void update(std::list<Enemy> *enemies, std::list<Laser> *lasers);

private:
    static bool _finish;
    static Ship *_ship;
    static float _crt_time;
    static float _last_spawned;
};

#endif