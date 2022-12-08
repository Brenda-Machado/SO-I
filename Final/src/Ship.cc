#include "Ship.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

Ship::Ship(Point centre, ALLEGRO_COLOR color, EventHandler *event_handler, std::list<Laser> *lasers)
{
    _centre = centre;
    _color = color;
    _event_handler = event_handler;
    _finish = false;
    _lasers = lasers;
    _last_shot = 0;
    _health = 3;
    _size = 10;
    _last_hurt = 0;
}
void Ship::get_hurt(float crt_time)
{
    if (crt_time - _last_hurt > 3)
    {
        _health -= 1;
        _last_hurt = crt_time;
    }
    if (_health == 0)
    {
        _finish = true;
    }
}
void Ship::createLaser()
{
    float crt_time = al_current_time();
    if (crt_time - _last_shot > 0.5)
    {
        _lasers->push_back(Laser(_centre + Vector(1000, 0) * 0.05, al_map_rgb(0, 0, 255), Vector(1000, 0)));
        _last_shot = crt_time;
    }
}
void Ship::start(Ship *ship)
{
    std::cout << "ship start" << std::endl;
    ship->run();
    std::cout << "ending ship" << std::endl;
    Thread::exit_running(3);
}
void Ship::run()
{
    std::cout << "ship run" << std::endl;
    _prev_time = 0;
    while (!_finish)
    {
        shipLoop();
    }
}
void Ship::shipLoop()
{
    std::cout << "Ship::shipLoop()" << std::endl;

    float crt_time = al_current_time();
    float dt = crt_time - _prev_time;

    setSpeed();
    _centre = _centre + _speed * dt;

    selectShipAnimation();
    _speed = Vector(0, 0);

    checkBoundary();

    _prev_time = crt_time;
    Thread::yield();
}
void Ship::setSpeed()
{

    if (_event_handler->get_pressed_keys(act::action::MOVE_UP))
    {
        _speed.y -= 250;
        std::cout << "u";
    }
    if (_event_handler->get_pressed_keys(act::action::MOVE_RIGHT))
    {
        _speed.x += 250;
        std::cout << "r";
    }
    if (_event_handler->get_pressed_keys(act::action::MOVE_DOWN))
    {
        _speed.y += 250;
        std::cout << "d";
    }
    if (_event_handler->get_pressed_keys(act::action::MOVE_LEFT))
    {
        _speed.x -= 250;
        std::cout << "l";
    }
    if (_event_handler->get_pressed_keys(act::action::FIRE_SECONDARY))
    {
        std::cout << "missel\n";
    }
    if (_event_handler->get_pressed_keys(act::action::FIRE_PRIMARY))
    {
        std::cout << "fire";
        createLaser();
    }
    std::cout << std::endl;
}
void Ship::checkBoundary()
{
    // check x bound and adjust if out
    if (_centre.x > 800 - 16)
        _centre.x = 800 - 16;
    else if (_centre.x < 16)
        _centre.x = 16;
    // check y bound and adjust if out
    if (_centre.y > 600 - 16)
        _centre.y = 600 - 16;
    else if (_centre.y < 16)
        _centre.y = 16;
}

void Ship::selectShipAnimation()
{
    if (_speed.x > 0)
    {
        _col = 1;
        if (_speed.y > 0)
            _row = 2;
        else if (_speed.y < 0)
            _row = 0;
        else
            _row = 1;
    }
    else
    {
        _col = 0;
        if (_speed.y > 0)
            _row = 2;
        else if (_speed.y < 0)
            _row = 0;
        else
            _row = 1;
    }
}