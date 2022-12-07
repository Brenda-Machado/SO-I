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
void Window::drawLaser(Laser laser)
{
   Point tracer = laser.centre + laser.speed * (-0.05);
   al_draw_line(laser.centre.x, laser.centre.y, tracer.x, tracer.y, laser.color, 3);
}

void Window::start(Window *window)
{
   window->run();
   std::cout << "exiting engine" << std::endl;
   Thread::exit_running(10);
}

Window::Window(ALLEGRO_EVENT_QUEUE *ev, ALLEGRO_DISPLAY *dis, ALLEGRO_TIMER *tim)
{
   _finish = false;
   _timer = tim;
   _eventQueue = ev;
   _display = dis;
   _event_handler = NULL;
   _enemy_controller = NULL;
   init();
}

Window::~Window()
{

   bg.reset();
   spikeBomb.reset();
   explosion.reset();
   _ship->sprite.reset();
   delete _event_handler;
   delete _ship;
   delete _enemy_controller;
   delete _boss;
}

// initialize Allegro, the _display window, the addons, the timers, and event
// sources
void Window::init()
{
   _event_handler = new EventHandler(_eventQueue);
   _enemy_controller = new EnemyController(&_control_enemies, &_enemy_lasers);

   // inicia _ship
   loadSprites();

   _event_thread = new Thread(EventHandler::start, _event_handler);
   _ship_thread = new Thread(Ship::start, _ship);
   _mine_thread = new Thread(Mine::start, &_mines, &_enemy_lasers);
   _controller_thread = new Thread(EnemyController::start, _enemy_controller);
   _boss_thread = new Thread(Boss::start, _boss);
}

// repeatedly call the state manager function until the _state is EXIT
void Window::run()
{
   float prevTime = 0;
   float tempPrevTime = 0;
   // main engine loop
   while (!_finish)
   {
      gameLoop(prevTime, tempPrevTime);
   }

   Mine::end();
   _mine_thread->join();
   delete _mine_thread;

   _ship->end();
   _ship_thread->join();
   delete _ship_thread;

   _event_handler->end();
   _event_thread->join();
   delete _event_thread;

   _enemy_controller->end();
   _controller_thread->join();
   delete _controller_thread;

   _boss->end();
   _boss_thread->join();
   delete _boss_thread;
}

void Window::gameLoop(float &prevTime, float &temp)
{
   std::cout << "Window::gameLoop()" << std::endl;
   ALLEGRO_EVENT event;
   bool redraw = true;
   float crtTime;

   // tirar depois, junto com update do player
   float tempcrttime = al_get_time();
   float tempDt = tempcrttime - temp;
   temp = tempcrttime;
   for (auto iter = _enemy_lasers.begin(); iter != _enemy_lasers.end(); iter++)
   {
      iter->update_pos(tempDt);
      if (!iter->active)
      {
         iter = _enemy_lasers.erase(iter);
      }
      else
      {
         iter++;
      }
   }

   if (_event_handler->get_pressed_keys(act::action::QUIT_GAME))
   {
      _finish = true;
      return;
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
   std::cout << "exiting gameLoop()" << std::endl;
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

   if (_boss->isAlive()) {
      drawBoss(_boss->_sprite, 0);
   }

   for (auto iter = _player_lasers.begin(); iter != _player_lasers.end(); iter++)
   {
      drawLaser(*iter);
   }

   for (auto iter = _enemy_lasers.begin(); iter != _enemy_lasers.end(); iter++)
   {
      drawLaser(*iter);
   }

   for (auto iter = _mines.begin(); iter != _mines.end(); iter++)
   {
      drawMine(spikeBomb, *iter);
   }
   std::cout << "number of enemies = " << _control_enemies.size() << std::endl;
   for (auto iter = _control_enemies.begin(); iter != _control_enemies.end(); iter++)
   {
      drawEnemy(&(*iter));
   }
}

void Window::drawShip(std::shared_ptr<Sprite> sprite, int flags)
{
   sprite->draw_region(_ship->get_row(), _ship->get_col(), 47.0, 40.0, _ship->get_centre(), flags);
}
void Window::drawMine(std::shared_ptr<Sprite> sprite, Mine mine)
{
   sprite->draw_region(mine.row, mine.col, 40.0, 41.0, mine.centre, 0);
}
void Window::drawBackground()
{
   bg->draw_parallax_background(bgMid.x, 0);
}
void Window::drawEnemy(Enemy *enem)
{
   enemy->draw_region(enem->get_row(), enem->get_col(), 47.0, 47.0, enem->getPosition(), 0);
}
void Window::drawBoss(std::shared_ptr<Sprite> sprite, int flags)
{
   sprite->draw_boss(_boss->get_row(), _boss->get_col(), 200, 200, _boss->getPosition(), flags);
}
void Window::loadSprites()
{
   // Create Ship
   _ship = new Ship(Point(215, 245), al_map_rgb(0, 200, 0), _event_handler, &_player_lasers);
   _boss = new Boss(Point(810, 300), Vector(-5,0), al_map_rgb(155, 0, 0));

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
   // explosion = std::make_shared<Sprite>("explode.png");
   spikeBomb = std::make_shared<Sprite>("spikebomb.png");

   // _ship->sprite = std::make_shared<Sprite>("/home/joao/Projects/UFSC/SO1/Final/src/resources/Sprite2.png"); // espaçonave do usuário
   // bg = std::make_shared<Sprite>("/home/joao/Projects/UFSC/SO1/Final/src/resources/BGstars.png");            // fundo da tela - background
   enemy = std::make_shared<Sprite>("EnemyBasic.png"); // inimigo
   _boss->_sprite = std::make_shared<Sprite>("bossv2.png");        // boss
   // delete path;
   al_destroy_path(path);

}
