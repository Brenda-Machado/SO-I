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
        // depois de um certo tempo
            // spawn_enemies();
        if (!_enemies->empty())
        {
            // update_enemies();
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