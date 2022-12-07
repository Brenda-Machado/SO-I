#include "EventHandler.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

#include "Timer.h"
void EventHandler::start(EventHandler *event_handler)
{
    event_handler->init();
    event_handler->run();
    Thread::exit_running(2);
}

void EventHandler::run()
{
    while (!_finish)
    {
        eventLoop();
    }
}

EventHandler::EventHandler(ALLEGRO_EVENT_QUEUE *_eventQueue)
{
    _eventQueue = _eventQueue;
    _finish = false;
}

EventHandler::~EventHandler()
{
    // if (_eventQueue != NULL)
    //     al_destroy_event_queue(_eventQueue);
}

void EventHandler::init()
{
}

void EventHandler::eventLoop()
{
    std::cout << "EventHandler::eventLoop()" << std::endl;
    ALLEGRO_KEYBOARD_STATE kb;

    al_get_keyboard_state(&kb);
    input(kb); // irá retornar uma tecla de ação. TODO: necessário transformar em Thread e fazer a ação
    Thread::yield();
}

void EventHandler::input(ALLEGRO_KEYBOARD_STATE &kb)
{
    _pressed_keys[act::action::MOVE_DOWN] = al_key_down(&kb, ALLEGRO_KEY_DOWN);
    _pressed_keys[act::action::MOVE_RIGHT] = al_key_down(&kb, ALLEGRO_KEY_RIGHT);
    _pressed_keys[act::action::MOVE_LEFT] = al_key_down(&kb, ALLEGRO_KEY_LEFT);
    _pressed_keys[act::action::FIRE_SECONDARY] = al_key_down(&kb, ALLEGRO_KEY_1);
    _pressed_keys[act::action::FIRE_PRIMARY] = al_key_down(&kb, ALLEGRO_KEY_SPACE);
    _pressed_keys[act::action::QUIT_GAME] = al_key_down(&kb, ALLEGRO_KEY_ESCAPE);
    _pressed_keys[act::action::MOVE_UP] = al_key_down(&kb, ALLEGRO_KEY_UP);
}