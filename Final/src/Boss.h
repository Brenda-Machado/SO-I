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

#include <list>

class Boss
{

public:
    Boss (Point _pos, Vector _spe, ALLEGRO_COLOR c, std::list<Laser> *lasers);
    ~Boss() {};
    std::shared_ptr<Sprite> _sprite;
    static void start(Boss *Boss);
    void run();
    void end()
    {
        _finish = true;
        std::cout << "called end Boss" << std::endl;
    }
    bool on_screen();
    void shoot();
    void hit();
    Point getPosition() { return _position; };
    void setPosition(Point position) { _position = position; };
    void kill() { _alive = false; };
    Vector getSpeed() { return _speed; };
    int getHp() { return _hp; };
    int getDamage() { return _damage; };
    bool isAlive() { return _alive; };
    inline int get_row() const { return _row; };
    inline int get_col() const { return _col; };
    void update(float dt);

private:
    void bossLoop();
    void selectbossAnimation();
    void createLaser();

    Point _position;
    Vector _speed;
    ALLEGRO_COLOR _color;
    int _hp;
    int _prev_time;
    int _row;
    int _col;
    int _last_spawn;
    int _damage;
    bool _alive;
    bool _finish;
    std::list<Laser> *_lasers;

};

#endif