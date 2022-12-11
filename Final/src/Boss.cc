#include "Boss.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

__USING_API

Boss::Boss(ALLEGRO_COLOR c, std::list<Laser> *lasers, std::list<Missile> *missiles)
{
    _position = Point(-500, -500);
    _finish = false;
    _hp = 0;
    _color = c;
    _size = 100;
    _row = 0;
    _col = 0;
    _lasers = lasers;
    _missiles = missiles;
    _max_hp = 100;

    _prev_time = 0;
    _last_laser = 0;
    _last_missile = 0;
    _last_missile_launched = 0;
    _last_barrage = 0;
    kill();
}

void Boss::start(Boss *Boss)
{
    Boss->run();
    Thread::exit_running(5);
}

void Boss::give_life()
{
    _alive = true;
    _position = Point(900, 300);
    _speed = Vector(-80, 0);
    _hp = _max_hp;
}

void Boss::run()
{
    std::cout << "Boss started" << std::endl;
    while (!_finish)
        bossLoop();
}

void Boss::bossLoop()
{

    std::cout << "BOSS COL = " << _col << std::endl;

    float _crt_time = al_current_time();

    if (_crt_time - _last_spawn > 10 && !_alive)
    {
        std::cout << "Boss spawn" << std::endl;
        give_life();
    }
    if (_alive)
    {
        update(_crt_time - _prev_time);
        selectbossAnimation();
        // shooting lasers
        if (_crt_time - _last_laser > 2 && on_screen())
        {
            shoot();
            _last_laser = _crt_time;
        }
        // missile barrage
        if (_crt_time - _last_barrage > 10)
        {
            if (_crt_time - _last_missile > 0.2 && _last_missile_launched < 10)
            {
                missile_atack();
                _last_missile = _crt_time;
                _last_missile_launched++;
            }
            else if (_last_missile_launched >= 10)
            {
                _last_barrage = _crt_time;
                _last_missile_launched = 0;
            }
        }
    }
    _prev_time = _crt_time;
    Thread::yield();
}

void Boss::selectbossAnimation()
{

    float to_comp = _max_hp;
    if (_hp <= to_comp * 0.33)
    {
        _col = 2;
        _row = 2;
    }
    else if (_hp <= to_comp * 0.66)
    {
        _col = 0;
        _row = 1;
    }
    else
    {
        _col = 0;
        _row = 0;
    }
}

bool Boss::on_screen()
{
    if (_position.x < 0 || _position.x > 800 || _position.y < 0 || _position.y > 600)
        return false;
    return true;
}

void Boss::update(float dt)
{
    if (_position.x < 700)
    {
        _speed.x = 0;
        _speed.y = 200;
        _position.x = 700;
    }
    else if (_position.y > 500 && _speed.y > 0)
    {
        _speed.reflectY();
    }
    else if (_position.y < 100 && _speed.y < 0)
    {
        std::cout << "REFLECTTTTINNNNNG\n";
        _speed.reflectY();
    }

    _position = _position + _speed * dt;
}

void Boss::shoot()
{

    // basic shoot
    for (int i = 0; i < 10; i++)
    {
        Vector speed = get_speed_degrees(500, 45, -45, i, 10);
        Laser laser = Laser(_position + _speed * 0.05, al_map_rgb(42, 128, 0), speed);
        _lasers->push_back(laser);
    }
}

void Boss::missile_atack()
{
    int min_degrees = 0;
    int max_degrees = 60;
    if (_position.y > 400)
    {
        min_degrees = 0;
        max_degrees = -45;
    }
    else if (_position.y < 200)
    {
        min_degrees = 0;
        max_degrees = 45;
    }
    else
    {
        min_degrees = -30;
        max_degrees = 30;
    }
    int missile_speed = 150;
    Missile missile1 = Missile(_position, get_speed_degrees(missile_speed, max_degrees, min_degrees, _last_missile_launched, 10));
    _missiles->push_back(missile1);
}
Vector Boss::get_speed_degrees(int speed, int max_degrees, int min_degrees, int iteration, int max_shots)
{
    float PI = std::acos(-1);
    float degree_increase = (max_degrees - min_degrees) / max_shots;
    float rad_increase = (PI / 180) * degree_increase;
    float min_rad = (PI / 180) * min_degrees;
    float crt_angle = (iteration * rad_increase) + min_rad;
    Vector normalized = Vector(std::cos(crt_angle), std::sin(crt_angle));

    return Vector(-1 * normalized.x * speed, normalized.y * speed);
}
void Boss::hit()
{
    _hp--;
    if (_hp <= 0)
    {
        kill();
    }
}
void Boss::kill()
{
    _alive = false;
    _position = Point(-500, -500);
    _last_spawn = al_get_time();
    _speed = Vector(0, 0);
}