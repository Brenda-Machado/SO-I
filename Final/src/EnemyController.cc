/**
 * @file
 * @brief
 *
 * @author
 * @bug
 */

#include "EnemyController.h"
void EnemyController::start(EnemyController *enemy_controller)
{
    enemy_controller->run();
    Thread::exit_running(7);
}

EnemyController::EnemyController(std::list<Enemy *> *enemies, std::list<Laser> *lasers)
{
    game_over = false;
    _enemies = enemies;
    _lasers = lasers;
    _last_spawn = -15;
    _last_shot = 0;
};

void EnemyController::run()
{
    float last_updated = 0;
    while (!game_over)
    {
        std::cout << "enemy loop" << std::endl;
        _crt_time = al_current_time();
        float dt = _crt_time - last_updated;
        last_updated = _crt_time;
        if (_crt_time - _last_spawn > 15)
        { // 15 segundos
            spawn_enemies();
            _last_spawn = _crt_time;
        }

        check_enemies(dt);

        Thread::yield();
    }
}

void EnemyController::spawn_enemies()
{
    std::cout << "spawn enemies" << std::endl;
    Enemy *enemy5 = new Enemy(Point(910, 500), Vector(-60, 0), _lasers);
    Enemy *enemy4 = new Enemy(Point(860, 400), Vector(-60, 0), _lasers);
    Enemy *enemy1 = new Enemy(Point(810, 300), Vector(-60, 0), _lasers);
    Enemy *enemy2 = new Enemy(Point(860, 200), Vector(-60, 0), _lasers);
    Enemy *enemy3 = new Enemy(Point(910, 100), Vector(-60, 0), _lasers);
    _enemies->push_back(enemy1);
    _enemies->push_back(enemy2);
    _enemies->push_back(enemy3);
    _enemies->push_back(enemy4);
    _enemies->push_back(enemy5);
}

void EnemyController::updateEnemy(Enemy *enemy, float dt)
{
    Point centre = enemy->getPosition();
    Vector speed = enemy->getSpeed();
    enemy->setPosition(centre + speed * dt);
    if (!enemy->in_bound())
    {
        enemy->kill();
    }
}

void EnemyController::check_enemies(float dt)
{
    bool has_fired = false;
    for (auto iter = _enemies->begin(); iter != _enemies->end();)
    {
        updateEnemy(*iter, dt);
        if (_crt_time - _last_shot > 3 && (*iter)->on_screen())
        {
            (*iter)->shoot();
            has_fired = true;
        }
        if (!(*iter)->isAlive())
        {

            std::cout << "KILLINGMURDERINGHONONONO" << std::endl;
            delete *iter;
            iter = _enemies->erase(iter);
        }
        else
        {
            iter++;
        }
    }
    _last_shot = (has_fired) ? _crt_time : _last_shot;
}

// mais metódos...
