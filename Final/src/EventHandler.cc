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
    std::cout << "eventHandler exited loop" << std::endl;
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
    _crt_event = input(kb); // irá retornar uma tecla de ação. TODO: necessário transformar em Thread e fazer a ação
    Thread::yield();
}

act::action EventHandler::input(ALLEGRO_KEYBOARD_STATE &kb)
{
    if (al_key_down(&kb, ALLEGRO_KEY_UP))
    {
        return act::action::MOVE_UP;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_RIGHT))
    {
        return act::action::MOVE_RIGHT;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_DOWN))
    {
        return act::action::MOVE_DOWN;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_LEFT))
    {
        return act::action::MOVE_LEFT;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_1))
    {
        std::cout << "missel\n";
        return act::action::FIRE_PRIMARY;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_SPACE))
    {
        std::cout << "tiro normal\n";
        return act::action::FIRE_SECONDARY;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE))
    {
        std::cout << "sair\n";
        return act::action::QUIT_GAME;
    }

    return act::action::NO_ACTION;
}