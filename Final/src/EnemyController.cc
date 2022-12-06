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
            check_enemies();
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
    for (int i = 0; i < 8; i++) {
        Enemy *enemy = new Enemy(Point(0,0), Vector(0,0), 0, 0, true);
        addEnemy(enemy);
    }
}

void EnemyController::updateEnemy(Enemy *enemy) 
{
    if (enemy->isAlive()) 
    {
        // atualiza a posição
    } else {
        removeEnemy(enemy);
    }
}

void EnemyController::check_enemies()
{
    for (auto iter = _enemies->begin(); iter != _enemies->end(); iter++)
   {
        updateEnemy(*iter);
   }
}

//mais metódos...

__END_API