/**
 * @file
 * @brief
 *
 * @author
 * @bug
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <memory>

#include <string>
#include "Vector.h"
#include "Point.h"
#include "Enemy.h"
#include "Mine.h"
#include "Sprite.h"
#include "time.h"
#include "Laser.h"
#include "Ship.h"
#include "Boss.h"
#include "Missile.h"

#include <list>

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
__USING_API

class GameController
{
public:
    GameController(Ship *ship, std::list<Laser> *enemy_lasers,
                   std::list<Laser> *player_lasers,
                   std::list<Mine> *mines,
                   std::list<Enemy *> *ememies,
                   Boss *boss,
                   std::list<Missile> *missiles);

    static void start(Ship *ship, std::list<Laser> *enemy_lasers,
                      std::list<Laser> *player_lasers,
                      std::list<Mine> *mines,
                      std::list<Enemy *> *enemies,
                      Boss *boss,
                      std::list<Missile> *missiles);
    static void end() { _finish = true; };

private:
    void run();
    void update_lasers(std::list<Laser> *lasers);
    void update_missiles(std::list<Missile> *missiles);
    void check_enemy_collisions();
    void check_mine_collisions();
    void check_player_collisions();
    void check_boss_collisions();
    void check_ship_missile_collisions();
    bool collision_happened(Point src, Point trgt, int size);
    bool enemy_has_colided(Enemy *enemy);
    bool mine_has_colided(Mine mine);
    void check_ship_enemy_collisions();
    void check_ship_mine_collisions();

private:
    Ship *_ship;
    Boss *_boss;
    std::list<Laser> *_enemy_lasers;
    std::list<Laser> *_player_lasers;
    std::list<Mine> *_mines;
    std::list<Enemy *> *_enemies;
    std::list<Missile> *_missiles;
    static bool _finish;
    float _last_update;
    float _crt_time;
};

#endif