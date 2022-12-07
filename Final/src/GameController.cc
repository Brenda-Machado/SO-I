#include "GameController.h"

bool GameController::_finish = false;

GameController::GameController(Ship *ship,
                               std::list<Laser> *enemy_lasers,
                               std::list<Laser> *player_lasers,
                               std::list<Mine> *mines,
                               std::list<Enemy> *enemies)
{
    _enemy_lasers = enemy_lasers;
    _player_lasers = player_lasers;
    _ship = ship;
    _mines = mines;
    _enemies = enemies;
    _last_update = 0;
    _crt_time = al_get_time();
}

void GameController::start(Ship *ship, std::list<Laser> *enemy_lasers,
                           std::list<Laser> *player_lasers,
                           std::list<Mine> *mines,
                           std::list<Enemy> *enemies)
{
    GameController controller = GameController(ship,
                                               enemy_lasers,
                                               player_lasers,
                                               mines,
                                               enemies);
    controller.run();
    Thread::exit_running(9);
}
void GameController::run()
{
    while (!_finish)
    {
        _crt_time = al_get_time();
        update_lasers(_player_lasers);
        update_lasers(_enemy_lasers);
        _last_update = _crt_time;
        Thread::yield();
    }
}
void GameController::update_lasers(std::list<Laser> *lasers)
{
    // updating player lasers
    for (auto laser = lasers->begin(); laser != lasers->end();)
    {
        laser->update_pos(_crt_time - _last_update);
        if (!laser->in_bound())
        {
            laser = lasers->erase(laser);
        }
        else
        {
            laser++;
        }
    }
}