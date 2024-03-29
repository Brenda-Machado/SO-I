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
#include "Font.h"

#include "EventHandler.h"
#include "thread.h"
#include "Ship.h"
#include "Laser.h"
#include "Mine.h"
#include "EnemyController.h"
#include "GameController.h"
#include "Sniper.h"
#include "Boss.h"

#include <list>
#include <vector>

__USING_API
// forward declarations
class Menu;
class Root;

class Window
{

public:
   Window(ALLEGRO_EVENT_QUEUE *ev, ALLEGRO_DISPLAY *dis, ALLEGRO_TIMER *tim);
   ~Window();

   void run();

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
   void init();
   void draw();
   void update(double dt);

   void gameLoop(float &prevTime);

   void drawShip(std::shared_ptr<Sprite> sprite, int flags);
   void drawMine(std::shared_ptr<Sprite> sprite, Mine mine);
   void drawBackground();
   void drawLaser(Laser laser);
   void drawEnemy(Enemy *enemy);
   void drawBoss(std::shared_ptr<Sprite> sprite, int flags);
   void drawMissile(Missile missile);
   void drawExplosion(Explosion explosion);
   void drawLife();
   void drawGameOver();
   
   // Background

   Point bgMid; /**<point used by the background to draw from */
   Point fgMid;
   Point fg2Mid;
   Vector bgSpeed; /**<background movement speed */
   Vector fgSpeed;
   std::shared_ptr<Sprite> bg; /**<shared pointer to background animation */
   std::shared_ptr<Sprite> fg;
   std::shared_ptr<Sprite> spikeBomb;
   std::shared_ptr<Sprite> _explosion;
   std::shared_ptr<Sprite> enemy; // enemy sprite

   // general game variables
   int _displayWidth;
   int _displayHeight;
   int _fps;
   std::list<Laser> _player_lasers;
   std::list<Mine> _mines;
   std::list<Laser> _enemy_lasers;
   std::list<Enemy *> _control_enemies;
   std::list<Missile> _missiles;
   std::list<Missile> _player_missiles;
   std::list<Explosion> _explosions;

   // missile frames
   std::vector<std::shared_ptr<Sprite>> _missile_frames;

   // allegro objects
   ALLEGRO_TIMER *_timer;
   ALLEGRO_EVENT_QUEUE *_eventQueue;
   ALLEGRO_DISPLAY *_display;
   ALLEGRO_FONT *font;
   
   bool _finish;
   bool _game_over;

   // Thread variables
   EventHandler *_event_handler;
   Thread *_event_thread;

   Ship *_ship;
   Thread *_ship_thread;

   Thread *_mine_thread;

   EnemyController *_enemy_controller;
   Thread *_controller_thread;

   Thread *_game_controller_thread;

   Thread *_sniper_thread;

   Boss *_boss;
   Thread *_boss_thread;
};

#endif