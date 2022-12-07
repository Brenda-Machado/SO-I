#include "Boss.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

__USING_API

Boss::Boss(Point _pos, Vector _spe,  ALLEGRO_COLOR c) {
    _position = _pos;
    _speed = _spe;
    _finish = false;
    _hp = 100;
    _damage = 10;
    _color = c;
    _row = 0;
    _col = 0;
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
    
    if (_crt_time - _last_spawn > 60) {
        std::cout << "Boss spawn" << std::endl;
        _alive = true;
        _last_spawn = _crt_time;
    }
    if (_alive) {
        update(_crt_time - _prev_time);
        selectbossAnimation();
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