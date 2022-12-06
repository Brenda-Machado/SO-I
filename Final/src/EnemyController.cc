/**
 * @file 
 * @brief
 *
 * @author
 * @bug
 */

#include "EnemyController.h"

__BEGIN_API

void EnemyController::start(EnemyController *enemy_controller)
{
    enemy_controller->run();
}

void EnemyController::run()
{
    while (!game_over)
    {   
        _crt_time = al_current_time();
        if (_crt_time - _last_spawn > 15000) { // 15 segundos
            spawn_enemies();
            std::cout << "spawn enemies" << std::endl;
            _last_spawn = _crt_time;
        }
        if (!_enemies->empty())
        {
            update_enemies(_last_spawn - _crt_time);
        }
    }
}

void EnemyController::addEnemy(Enemy *enemy)
{   
    _enemies->push_back(enemy); 
}

void EnemyController::removeEnemy(Enemy *enemy)
{   
    _enemies->remove(enemy);
}

void EnemyController::spawn_enemies()
{   

}

void EnemyController::update_enemies(float dt)
{

}


//mais metódos...

__END_API