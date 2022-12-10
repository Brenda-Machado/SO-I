#include "Boss.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

__USING_API

Boss::Boss(Point _pos, Vector _spe,  ALLEGRO_COLOR c, std::list<Laser> *lasers, std::list<Missile> *missiles) {
    _position = _pos;
    _speed = _spe;
    _finish = false;
    _hp = 5;
    _damage = 10;
    _color = c;
    _row = 0;
    _col = 0;
    _lasers = lasers;
    _missiles = missiles;
}

void Boss::start(Boss *Boss) {
    Boss->run();
    Thread::exit_running(5);
}

void Boss::run() {
    std::cout << "Boss started" << std::endl;
    _last_spawn = 0;
    while (!_finish)
        bossLoop();
}

void Boss::bossLoop() {
    std::cout << "Boss::bossLoop()" << std::endl;

    float _crt_time = al_current_time();
    
    if (_crt_time - _last_spawn > 6) {
        std::cout << "Boss spawn" << std::endl;
        _alive = true;
        _last_spawn = _crt_time;
    }
    if (_alive) {
        update(_crt_time - _prev_time);
        selectbossAnimation();
        // if (_crt_time - _prev_time > 5 && _position.x < 600) {
        //     shoot();  
        // }
        if (_crt_time - _prev_time > 10) {
            missile_atack();
        }
    }
    _prev_time = _crt_time;
    Thread::yield();
}

void Boss::selectbossAnimation() {

    if (_hp >= 80) {
        _col = 0;
    }
    if (_hp < 80 && _hp >= 40) { 
        _col = 1;
    }
    if (_hp < 40) {
        _col = 2;
    }
}

bool Boss::on_screen() {
    if (_position.x < 0 || _position.x > 800 || _position.y < 0 || _position.y > 600)
        return false;
    return true;
}

void Boss::update(float dt) {

    _position.x += _speed.x * dt;
    _position.y += _speed.y * dt;
   
    if(_position.x < 600) {
        _speed.x = 0;        
        _speed.y = 1;
    }
    if (_position.y > 300 && _speed.y > 0) { 
        _speed.reflectY();
    }
    if (_position.y < 300 && _speed.y < 0) { 
        _speed.reflectY();
    }
}

void Boss::shoot() {

    // basic shoot
    
    Laser laser1 = Laser(Point(_position.x-100, _position.y + 20), al_map_rgb(200, 0, 0), Vector(-420, 0));
    Laser laser2 = Laser(Point(_position.x-100, _position.y + 10), al_map_rgb(200, 0, 0), Vector(-420, 0));
    Laser laser3 = Laser(Point(_position.x-100, _position.y), al_map_rgb(200, 0, 0), Vector(-420, 0));
    Laser laser4 = Laser(Point(_position.x-100, _position.y - 10), al_map_rgb(200, 0, 0), Vector(-420, 0));
    Laser laser5 = Laser(Point(_position.x-100, _position.y - 20), al_map_rgb(200, 0, 0), Vector(-420, 0));
    _lasers->push_back(laser1);
    _lasers->push_back(laser2);
    _lasers->push_back(laser3);
    _lasers->push_back(laser4);
    _lasers->push_back(laser5); 
}

void Boss::missile_atack() {

    Missile missile1 = Missile(_position, Vector(-20, 0));
    Missile missile2 = Missile(_position, Vector(-20, 0));
    _missiles->push_back(missile1);
    _missiles->push_back(missile2);
}
void Boss::hit() {
    _hp -= -1;
    if (_hp <= 0) {
        _alive = false;
        _hp = 5;
        _last_spawn = al_current_time(); // só volta daqui 60 sec
    }
}