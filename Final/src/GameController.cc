#include "GameController.h"

bool GameController::_finish = false;

GameController::GameController(Ship *ship,
                               std::list<Laser> *enemy_lasers,
                               std::list<Laser> *player_lasers,
                               std::list<Mine> *mines,
                               std::list<Enemy> *enemies,
                               Boss *boss, std::list<Laser> *boss_lasers)
{
    _enemy_lasers = enemy_lasers;
    _player_lasers = player_lasers;
    _ship = ship;
    _mines = mines;
    _enemies = enemies;
    _last_update = 0;
    _crt_time = al_get_time();
    _boss = boss;
    _boss_lasers = boss_lasers;
}

void GameController::start(Ship *ship, std::list<Laser> *enemy_lasers,
                           std::list<Laser> *player_lasers,
                           std::list<Mine> *mines,
                           std::list<Enemy> *enemies,
                           Boss *boss, std::list<Laser> *boss_lasers)
{
    GameController controller = GameController(ship,
                                               enemy_lasers,
                                               player_lasers,
                                               mines,
                                               enemies, 
                                               boss, 
                                               boss_lasers);
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
        update_lasers(_boss_lasers);
        check_enemy_collisions();
        check_mine_collisions();
        check_boss_collisions();
        _last_update = _crt_time;
        Thread::yield();
    }
}
void GameController::update_lasers(std::list<Laser> *lasers)
{
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

bool GameController::collision_happened(Point src, Point trgt, int size)
{
    int dx = std::abs(trgt.x - src.x);
    int dy = std::abs(trgt.y - src.y);
    return ((dx * dx) + (dy * dy) <= size * size);
}
void GameController::check_enemy_collisions()
{
    for (auto enemy = _enemies->begin(); enemy != _enemies->end();)
    {
        if (enemy_has_colided(*enemy))
        {
            enemy = _enemies->erase(enemy);
        }
        else
        {
            enemy++;
        }
    }
}
bool GameController::enemy_has_colided(Enemy enemy)
{
    for (auto laser = _player_lasers->begin(); laser != _player_lasers->end(); laser++)
    {
        if (collision_happened(laser->centre, enemy.getPosition(), enemy.get_size()))
        {
            _player_lasers->erase(laser);
            return true;
        }
    }
    return false;
}
void GameController::check_mine_collisions()
{
    for (auto enemy = _mines->begin(); enemy != _mines->end();)
    {
        if (mine_has_colided(*enemy))
        {
            enemy = _mines->erase(enemy);
        }
        else
        {
            enemy++;
        }
    }
}
bool GameController::mine_has_colided(Mine mine)
{
    for (auto laser = _player_lasers->begin(); laser != _player_lasers->end(); laser++)
    {
        if (collision_happened(laser->centre, mine.centre, mine.size))
        {
            _player_lasers->erase(laser);
            return true;
        }
    }
    return false;
}

void GameController::check_boss_collisions()
{
    if (_boss->isAlive())
    {
        for (auto laser = _player_lasers->begin(); laser != _player_lasers->end(); laser++)
        {
            if (collision_happened(laser->centre, _boss->getPosition(), 200))
            {
                _player_lasers->erase(laser);
                _boss->hit();
                return;
            }
        }
        // for (auto laser = _boss_lasers->begin(); laser != _boss_lasers->end(); laser++)
        // {
        //     if (collision_happened(laser->centre, _ship->getPosition(), _ship->get_size()))
        //     {
        //         _boss_lasers->erase(laser);
        //         // _ship->hit();
        //         return;
        //     }
        // }
    }
}
