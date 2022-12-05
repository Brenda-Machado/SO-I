/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>

#include "Sprite.h"
#include "Vector.h"
#include "Action.h"

#include "EventHandler.h"
#include "thread.h"
#include "Ship.h"
__USING_API
// forward declarations
class Menu;
class Root;

class Window
{

public:
   Window(int w, int h, int fps);
   ~Window();

   void init();
   void run();
   void draw();
   void update(double dt);

   void gameLoop(float &prevTime);

   // void moveShip();
   void drawShip(std::shared_ptr<Sprite> sprite, int flags);
   void drawBackground();

   static void start(Window *engine);

   inline int getWidth() const
   {
      return _displayWidth;
   }
   inline int getHeight() const
   {
      return _displayHeight;
   }

private:
   void loadSprites();

   // Background
   Point bgMid; /**<point used by the background to draw from */
   Point fgMid;
   Point fg2Mid;
   Vector bgSpeed; /**<background movement speed */
   Vector fgSpeed;
   std::shared_ptr<Sprite> bg; /**<shared pointer to background animation */
   std::shared_ptr<Sprite> fg;

   // general game variables
   int _displayWidth;
   int _displayHeight;
   int _fps;
   // allegro objects
   ALLEGRO_TIMER *_timer;
   ALLEGRO_EVENT_QUEUE *_eventQueue;
   ALLEGRO_DISPLAY *_display;

   bool _finish;

   // Thread variables
   EventHandler *_event_handler;
   Thread *_event_thread;

   Ship *_ship;
   Thread *_ship_thread;
};

#endif