/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef SHIP_H
#define SHIP_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "Sprite.h"
#include "Vector.h"
#include "Action.h"

#include "EventHandler.h"
#include "thread.h"
#include "Laser.h"

#include <list>
__USING_API
class Ship
{
public:
    Ship(Point centre, ALLEGRO_COLOR color, EventHandler *event_handler, std::list<Laser> *lasers);
    static void start(Ship *ship);
    void run();
    void get_hurt(float crt_time);

    std::shared_ptr<Sprite> sprite;
    void end()
    {
        _finish = true;
        std::cout << "called end Ship" << std::endl;
    }
    inline Point get_centre() const { return _centre; };
    inline ALLEGRO_COLOR get_color() const { return _color; };
    inline Vector get_speed() const { return _speed; };
    inline int get_row() const { return _row; };
    inline int get_col() const { return _col; };
    inline int get_size() const { return _size; };
    inline int get_end() const { return _finish; };
    inline int get_health() const { return _health; };

private:
    void shipLoop();
    void selectShipAnimation();
    void checkBoundary();
    void setSpeed();
    void createLaser();

    Point _centre;
    ALLEGRO_COLOR _color;
    Vector _speed;
    int _row;
    int _col;
    bool _finish;
    int _vel;
    EventHandler *_event_handler;

    float _prev_time;
    float _last_shot;
    float _last_hurt;

    std::list<Laser> *_lasers;
    int _health;
    int _size;
};
#endif
