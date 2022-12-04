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
__BEGIN_API
class EventHandler
{
public:
    EventHandler(ALLEGRO_EVENT_QUEUE *_eventQueue);
    ~EventHandler();
    void init();
    void run();
    static void start(EventHandler *event_handler);
    void eventLoop();
    act::action input(ALLEGRO_KEYBOARD_STATE &);
    void end()
    {
        _finish = true;
    }

    inline act::action get_crt_event() const
    {
        return _crt_event;
    }

private:
    // general game variables
    // allegro objects
    // ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    act::action _crt_event;
    bool _finish;
};

#endif
__END_API