#include "GameController.h"

bool GameController::_finish = false;

GameController::GameController(Ship *ship,
                               std::list<Laser> *enemy_lasers,
                               std::list<Laser> *player_lasers,
                               std::list<Mine> *mines,
                               std::list<Enemy *> *enemies,
                               Boss *boss, std::list<Laser> *boss_lasers,
                               std::list<Missile> *missiles)
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
    _missiles = missiles;
}

void GameController::start(Ship *ship, std::list<Laser> *enemy_lasers,
                           std::list<Laser> *player_lasers,
                           std::list<Mine> *mines,
                           std::list<Enemy *> *enemies,
                           Boss *boss, std::list<Laser> *boss_lasers,
                           std::list<Missile> *missiles)
{
    GameController controller = GameController(ship,
                                               enemy_lasers,
                                               player_lasers,
                                               mines,
                                               enemies,
                                               boss,
                                               boss_lasers,
                                               missiles);
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
        update_missiles(_missiles);
        check_enemy_collisions();
        check_mine_collisions();
        check_boss_collisions();
        check_player_collisions();
        check_ship_enemy_collisions();
        check_ship_mine_collisions();
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
            delete *enemy;
            enemy = _enemies->erase(enemy);
        }
        else
        {
            enemy++;
        }
    }
}
bool GameController::enemy_has_colided(Enemy *enemy)
{
    for (auto laser = _player_lasers->begin(); laser != _player_lasers->end(); laser++)
    {
        if (collision_happened(laser->centre, enemy->getPosition(), enemy->get_size()))
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

void GameController::check_player_collisions()
{
    for (auto laser = _enemy_lasers->begin(); laser != _enemy_lasers->end();)
    {
        if (collision_happened(laser->centre, _ship->get_centre(), _ship->get_size()))
        {
            laser = _enemy_lasers->erase(laser);
            _ship->get_hurt(_crt_time);
        }
        else
            laser++;
    }
}
void GameController::check_ship_enemy_collisions()
{
    for (auto enemy = _enemies->begin(); enemy != _enemies->end();)
    {
        if (collision_happened(_ship->get_centre(),
                               (*enemy)->getPosition(),
                               _ship->get_size() + (*enemy)->get_size()))
        {
            _ship->get_hurt(_crt_time);
            delete *enemy;
            enemy = _enemies->erase(enemy);
        }
        else
            enemy++;
    }
}

void GameController::check_ship_mine_collisions()
{

    for (auto enemy = _mines->begin(); enemy != _mines->end();)
    {
        if (collision_happened(_ship->get_centre(),
                               enemy->centre,
                               _ship->get_size() + enemy->size))
        {
            _ship->get_hurt(_crt_time);
            enemy = _mines->erase(enemy);
        }
        else
            enemy++;
    }
}

void GameController::check_boss_collisions()
{
    if (_boss->isAlive())
    {
        // for (auto laser = _player_lasers->begin(); laser != _player_lasers->end(); laser++)
        // {
        //     if (collision_happened(laser->centre, _boss->getPosition(), 200))
        //     {
        //         _player_lasers->erase(laser);
        //         _boss->hit();
        //         return;
        //     }
        // }
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

void GameController::update_missiles(std::list<Missile> *missiles)
{
    for (auto missile = missiles->begin(); missile != missiles->end();)
    {
        missile->update_pos(_crt_time - _last_update);
        if (!missile->in_bound())
        {
            missile = missiles->erase(missile);
        }
        else
        {
            missile++;
        }
    }
}