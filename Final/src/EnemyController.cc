/**
 * @file 
 * @brief
 *
 * @author
 * @bug
 */

#include "EnemyController.h"

__BEGIN_API


EnemyController::EnemyController()
{
    game_over = false;
    _last_spawn = 0;
    crt_time = 0;
};

EnemyController::~EnemyController()
{
    delete _enemies;
}

void EnemyController::start()
{   
    for(auto i = 0; i < 8; i++)
        _initial_positions->push_back(Point(0,0));
    crt_time = al_current_time();
    _last_spawn = crt_time;
    
    while (!game_over) 
    {
        if (crt_time - _last_spawn > 1)
        {
            spawn_enemies(8);
            _last_spawn = crt_time;
        }
        if (_enemies.size() > 0)
        {   
            float dt = crt_time - _last_spawn;
            update_enemies(float dt);
        }
    }
}

void EnemyController::spawn_enemies(int number_enemies)
{   
    for (auto i = 0; i < number_enemies; i++)
    {
        Enemy _enemy = new Enemy(Point _initial_positions[i], Vector (1,0), int 5, int 0, bool true);
        _enemies.insert(_enemy);
        _enemy.spawn();
    }
}

void EnemyController::update_enemies(float dt)
{
    for (auto i = 0; i < _enemies.size(); i++)
    {
        _enemies[i]->update(dt);
    }
}

//mais metódos...

__END_API