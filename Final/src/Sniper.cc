#include "Sniper.h"
bool Sniper::_finish = false;
Ship *Sniper::_ship = nullptr;
float Sniper::_last_spawned = 0;
float Sniper::_crt_time = 0;
Sniper::Sniper(Point _pos, Vector _spe, std::list<Laser> *lasers)
{
    _row = 0;
    _col = 0;
    _size = 30;
    _alive = true;
    _position = _pos;
    _speed = _spe;
    _lasers = lasers;
}
void Sniper::shoot()
{
    std::cout << "sniper shooted\n";
    float dx = _ship->get_centre().x - _position.x;
    float dy = _ship->get_centre().y - _position.y;
    float hip = std::sqrt(dx * dx + dy * dy);
    float nx = dx / hip;
    float ny = dy / hip;
    float fx = 1300 * nx;
    float fy = 1300 * ny;
    Vector speed = Vector(fx, fy);
    Point pos = _position + speed * 0.05;
    Laser laser = Laser(pos, al_map_rgb(255, 0, 0), speed);
    _lasers->push_back(laser);
}
void Sniper::start_controller(std::list<Laser> *lasers, std::list<Enemy *> *enemies, Ship *ship)
{
    _ship = ship;
    while (!_finish)
    {
        _crt_time = al_get_time();
        spawn(enemies, lasers);
        Thread::yield();
    }
    Thread::exit_running(11);
}
void Sniper::spawn(std::list<Enemy *> *enemies, std::list<Laser> *lasers)
{
    if (_crt_time - _last_spawned < 20)
        return;
    Sniper *s1 = new Sniper(Point(810, 570), Vector(-80, 0), lasers);
    Sniper *s2 = new Sniper(Point(810, 30), Vector(-80, 0), lasers);
    enemies->push_back(s1);
    enemies->push_back(s2);
    _last_spawned = _crt_time;
}