/**
 * @file 
 * @brief
 *
 * @author
 * @bug
 */

#include "EnemyController.h"

Ordered_List<Enemy> EnemyController::enemies;

EnemyController::EnemyController()
{
    game_over = false;
}

EnemyController::~EnemyController()
{
    delete enemies;
}

void EnemyController::start()
{   
    crt_time = al_current_time();
    _last_spawn = crt_time;
    
    while (!game_over) 
    {
        if (crt_time - _last_spawn > 1)
        {
            spawn_enemies(8);
            _last_spawn = crt_time;
        }
        if (enemies.size() > 0)
        {
            update_enemies();
        }
    }
}

void EnemyController::spawn_enemies(int number_enemies)
{   
    for (int i = 0; i < number_enemies; i++)
    {
        Enemy *enemy = new Enemy();
        enemies.insert(enemy);
    }
    for (Enemy *enemy : enemies)
    {
        enemy->spawn();
    }
}

void EnemyController::update_enemies()
{
    for (Enemy *enemy : enemies)
    {
        enemy->update();
    }
}

//mais metódos...