#include "Window.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

#include "Timer.h"
void Window::start(Window *window)
{
   window->run();
   std::cout << "exiting engine" << std::endl;
   Thread::exit_running(10);
}
Window::Window(int w, int h, int fps)
{
   _displayWidth = w;
   _displayHeight = h;
   _fps = fps;
   _finish = false;
   _timer = NULL;
   _eventQueue = NULL;
   _event_handler = NULL;
   init();
}

Window::~Window()
{
   if (_timer != NULL)
      al_destroy_timer(_timer);
   if (_eventQueue != NULL)
      al_destroy_event_queue(_eventQueue);
   if (_display != NULL)
      al_destroy_display(_display);

   bg.reset();
   _ship->sprite.reset();
   delete _event_handler;
   delete _ship;
}

// initialize Allegro, the _display window, the addons, the timers, and event
// sources
void Window::init()
{
   // initialize allegro
   al_init();
   // create the display
   if ((_display = al_create_display(_displayWidth, _displayHeight)) == NULL)
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
   if ((_timer = al_create_timer(1.0 / _fps)) == NULL)
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

   _event_handler = new EventHandler(_eventQueue);

   // inicia _ship
   loadSprites();

   _event_thread = new Thread(EventHandler::start, _event_handler);
   _ship_thread = new Thread(Ship::start, _ship);
}

// repeatedly call the state manager function until the _state is EXIT
void Window::run()
{
   float prevTime = 0;
   // main engine loop
   while (!_finish)
   {
      gameLoop(prevTime);
   }

   _ship->end();
   _ship_thread->join();
   delete _ship_thread;

   _event_handler->end();
   _event_thread->join();
   delete _event_thread;
}

void Window::gameLoop(float &prevTime)
{
   std::cout << "Window::gameLoop()" << std::endl;
   ALLEGRO_EVENT event;
   bool redraw = true;
   float crtTime;

   if (_event_handler->get_pressed_keys(act::action::QUIT_GAME))
   {
      std::cout << "sair\n";
   }

   // get event
   al_wait_for_event(_eventQueue, &event);

   // _display closes
   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
   {
      _finish = true;
      return;
   }

   // timer
   if (event.type == ALLEGRO_EVENT_TIMER)
   {
      crtTime = al_current_time();
      update(crtTime - prevTime);
      prevTime = crtTime;
      redraw = true;
   }

   // render
   if (redraw && al_is_event_queue_empty(_eventQueue))
   {
      redraw = false;
      draw();
      al_flip_display();
   }
   Thread::yield();
}

// update the game mode
void Window::update(double dt)
{
   // background
   bgMid = bgMid + bgSpeed * dt;
   if (bgMid.x >= 800)
   {
      bgMid.x = 0;
   }
}

// draws for the game mode
void Window::draw()
{
   drawBackground();
   drawShip(_ship->sprite, 0);
}

void Window::drawShip(std::shared_ptr<Sprite> sprite, int flags)
{
   sprite->draw_region(_ship->get_row(), _ship->get_col(), 47.0, 40.0, _ship->get_centre(), flags);
}
void Window::drawBackground()
{
   bg->draw_parallax_background(bgMid.x, 0);
}

void Window::loadSprites()
{
   // Create Ship
   _ship = new Ship(Point(215, 245), al_map_rgb(0, 200, 0), _event_handler);

   // represents the middle of the image width-wise, and top height-wise
   bgMid = Point(0, 0);
   fgMid = Point(800, 0);
   fg2Mid = Point(300, 300);
   bgSpeed = Vector(50, 0);
   fgSpeed = Vector(-90, 0);

   // Go to resources directory
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   // sprites
   _ship->sprite = std::make_shared<Sprite>("Sprite2.png"); // espaçonave do usuário
   bg = std::make_shared<Sprite>("BGstars.png");            // fundo da tela - background
   // delete path
   al_destroy_path(path);
}