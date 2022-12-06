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
    for(i = 0; i < 8; i++)
        _initial_positions->push_back(Point(0,0));

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
            float dt = crt_time - _last_spawn;
            update_enemies(float dt);
        }
    }
}

void EnemyController::spawn_enemies(int number_enemies)
{   
    for (int i = 0; i < number_enemies; i++)
    {
        Enemy *enemy = new Enemy(Point _initial_positions[i], Vector (1,0), int 5, int 0, bool true);
        enemies.insert(enemy);
    }
    for (Enemy *enemy : enemies)
    {
        enemy->spawn();
    }
}

void EnemyController::update_enemies(float dt)
{
    for (Enemy *enemy : enemies)
    {
        enemy->update(dt);
    }
}

//mais metódos...