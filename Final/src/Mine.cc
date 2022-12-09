#include "Mine.h"
#include <allegro5/allegro.h>
#include <iostream>
bool Mine::_finish = false;
void Mine::start(std::list<Mine> *mines, std::list<Laser> *lasers)
{
    float last_spawned = 0;
    float last_time = 0;
    while (!_finish)
    {
        std::cout << "mine loop" << std::endl;
        float crt_time = al_get_time();
        if (crt_time - last_spawned > 30)
        {
            std::cout << "spawned mine" << std::endl;
            mines->push_back(Mine(Point(850, 300), Vector(-50, 0), lasers));
            last_spawned = crt_time;
        }

        for (auto mine = mines->begin(); mine != mines->end();)
        {
            mine->update_pos(crt_time - last_time);
            if (crt_time - mine->creation_time > 5)
            {
                mine->explode();
                mine = mines->erase(mine);
            }
            else
            {
                mine++;
            }
        }
        last_time = crt_time;
        Thread::yield();
    }
    Thread::exit_running(5);
}

void Mine::end() { _finish = true; };

Mine::Mine(Point cent, Vector spe, std::list<Laser> *lsr)
{
    col = 0;
    row = 0;
    centre = cent;
    speed = spe;
    lasers = lsr;
    creation_time = al_get_time();
    size = 20;
}

void Mine::update_pos(float dt)
{
    centre = centre + speed * dt;
}
void Mine::explode()
{
    Laser laser1 = Laser(centre, al_map_rgb(0, 255, 0), Vector(-600, 0));
    Laser laser2 = Laser(centre, al_map_rgb(0, 255, 0), Vector(600, 0));
    Laser laser3 = Laser(centre, al_map_rgb(0, 255, 0), Vector(0, 600));
    Laser laser4 = Laser(centre, al_map_rgb(0, 255, 0), Vector(0, -600));
    Laser laser5 = Laser(centre, al_map_rgb(0, 255, 0), Vector(420, 420));
    Laser laser6 = Laser(centre, al_map_rgb(0, 255, 0), Vector(420, -420));
    Laser laser7 = Laser(centre, al_map_rgb(0, 255, 0), Vector(-420, 420));
    Laser laser8 = Laser(centre, al_map_rgb(0, 255, 0), Vector(-420, -420));
    lasers->push_back(laser1);
    lasers->push_back(laser2);
    lasers->push_back(laser3);
    lasers->push_back(laser4);
    lasers->push_back(laser5);
    lasers->push_back(laser6);
    lasers->push_back(laser7);
    lasers->push_back(laser8);
}