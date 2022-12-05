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
    while (!game_over) 
    {
        // adicionar controle do tempo
        spawn_enemies(10);
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

void EnemyController::update_enemies(float dt)
{
    for (Enemy *enemy : enemies)
    {
        enemy->update(dt);
    }
}

//mais metódos...