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
#include "Sprite.h"
#include "time.h"
#include "Laser.h"

#include <list>

#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H

__USING_API

class EnemyController
{
public:
    EnemyController(std::list<Enemy *> *enemies, std::list<Laser> *lasers);
    ~EnemyController(){};
    static void start(EnemyController *enemy_controller);
    void run();
    void updateEnemy(Enemy *enemy, float dt);
    void spawn_enemies();
    void check_enemies(float dt);
    void end()
    {
        game_over = true;
        _enemies->clear();
    };
    // mais classes conforme necessário
private:
    bool game_over;
    std::list<Laser> *_lasers;
    std::list<Enemy *> *_enemies;
    float _last_spawn;
    float _last_shot;
    float _crt_time;
};
#endif