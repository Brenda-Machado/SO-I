#ifndef main_class_h
#define main_class_h

#include <iostream>
#include "traits.h"
#include "Window.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <ctime>
#include <cstdlib>
#include <string>

__BEGIN_API

class Main
{
public:
    Main()
    {
    }

    static void run(void *name)
    {
        srand(time(0));
        start_allegro(800, 600, 60);
        Window *window = new Window(_eventQueue, _display, _timer);
        Thread *window_thread = new Thread(Window::start, window);
        window_thread->join();
        delete window;
        delete window_thread;

        if (_timer != NULL)
            al_destroy_timer(_timer);
        if (_eventQueue != NULL)
            al_destroy_event_queue(_eventQueue);
        if (_display != NULL)
            al_destroy_display(_display);

        Thread::exit_running(0);
        std::cout << "ended" << std::endl;
    }

    static void start_allegro(int width, int height, int fps)
    {
        // initialize allegro
        al_init();
        // create the display
        if ((_display = al_create_display(width, height)) == NULL)
        {
            std::cout << "Cannot initialize the display\n";
            exit(1);
        }
        // initialize addons
        al_init_primitives_addon();
        al_init_font_addon();
        al_init_ttf_addon();
        al_init_image_addon();
        // initialize our timers
        if ((_timer = al_create_timer(1.0 / fps)) == NULL)
        {
            std::cout << "error, could not create timer\n";
            exit(1);
        }
        if ((_eventQueue = al_create_event_queue()) == NULL)
        {
            std::cout << "error, could not create event queue\n";
            exit(1);
        }
        // register our allegro _eventQueue
        al_register_event_source(_eventQueue, al_get_display_event_source(_display));
        al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
        al_start_timer(_timer);
        // // install keyboard
        if (!al_install_keyboard())
        {
            std::cerr << "Could not install keyboard\n";
        }

        // register keyboard
        al_register_event_source(_eventQueue, al_get_keyboard_event_source());
    }

    ~Main() {}

private:
    // allegro objects
    static ALLEGRO_TIMER *_timer;
    static ALLEGRO_EVENT_QUEUE *_eventQueue;
    static ALLEGRO_DISPLAY *_display;
};

__END_API

#endif
