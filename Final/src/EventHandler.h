/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "Sprite.h"
#include "Vector.h"
#include "Action.h"
#include "thread.h"
#include <unordered_map>
__USING_API
class EventHandler
{
public:
    EventHandler(ALLEGRO_EVENT_QUEUE *_eventQueue);
    ~EventHandler();
    void init();
    void run();
    static void start(EventHandler *event_handler);
    void eventLoop();
    void input(ALLEGRO_KEYBOARD_STATE &);
    void end()
    {
        _finish = true;
        std::cout << "called end Event handler" << std::endl;
    }

    inline bool get_pressed_keys(act::action name) const
    {
        if (_pressed_keys.find(name) != _pressed_keys.end())
        {
            return _pressed_keys.at(name);
        }
        return false;
    }

private:
    // general game variables
    // allegro objects
    // ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    bool _finish;
    std::unordered_map<act::action, bool> _pressed_keys;
};

#endif