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
#include "EventHandler.h"
__USING_API
class Ship
{
public:
    Ship(Point centre, ALLEGRO_COLOR color, EventHandler *event_handler);
    static void start(Ship *ship);
    void run();

    std::shared_ptr<Sprite> sprite;
    void end()
    {
        _finish = true;
        std::cout << "called end Ship" << std::endl;
    }
    inline Point get_centre() const
    {
        return _centre;
    }
    inline ALLEGRO_COLOR get_color() const
    {
        return _color;
    }
    inline Vector get_speed() const
    {
        return _speed;
    }
    inline int get_row() const
    {
        return _row;
    }
    inline int get_col() const
    {
        return _col;
    }

private:
    void shipLoop();
    void selectShipAnimation();
    void checkBoundary();
    void setSpeed();

    Point _centre;
    ALLEGRO_COLOR _color;
    Vector _speed;
    int _row;
    int _col;
    bool _finish;
    EventHandler *_event_handler;
    float _prev_time;
};
#endif
