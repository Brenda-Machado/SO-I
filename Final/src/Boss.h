#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <string>
#include <list>
#include <iostream>

#ifndef BOSS_H
#define BOSS_H

#include "Sprite.h"
#include "Vector.h"
#include "Point.h"
#include "Laser.h"
#include "thread.h"
#include "Missile.h"

#include <list>

class Boss
{

public:
    Boss(ALLEGRO_COLOR c, std::list<Laser> *lasers, std::list<Missile> *missiles);
    ~Boss(){};
    static void start(Boss *Boss);
    void run();
    void end()
    {
        _finish = true;
        std::cout << "called end Boss" << std::endl;
    }
    bool on_screen();
    void shoot();
    void missile_atack();
    void hit();

    // getter e setters
    Point getPosition() { return _position; };
    void setPosition(Point position) { _position = position; };
    void kill();
    void give_life();
    Vector getSpeed() { return _speed; };
    int getHp() { return _hp; };
    int getSize() { return _size; };
    bool isAlive() { return _alive; };
    inline int get_row() const { return _row; };
    inline int get_col() const { return _col; };
    void update(float dt);

public:
    std::shared_ptr<Sprite> _sprite;

private:
    void bossLoop();
    void selectbossAnimation();
    Vector get_speed_degrees(int speed, int max_degrees, int min_degrees, int iteration, int max_shots);

private:
    Point _position;
    Vector _speed;
    ALLEGRO_COLOR _color;

    float _prev_time;
    float _last_spawn;
    float _last_missile;
    float _last_laser;
    float _last_barrage;

    int _hp;
    int _row;
    int _col;
    int _last_missile_launched;
    int _size;
    int _max_hp;
    bool _alive;
    bool _finish;
    std::list<Laser> *_lasers;
    std::list<Missile> *_missiles;
};

#endif