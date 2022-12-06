/**
 * @file 
 * @brief
 *
 * @author
 * @bug
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <memory>

#include <string>
#include "Vector.h"
#include "Point.h"
#include "Enemy.h"
#include "Sprite.h"
#include "time.h"
#include <list>

__BEGIN_API

class EnemyController
{
public:
    EnemyController();
    ~EnemyController();
    void start();
    void spawn_enemies(int number_enemies);
    void update_enemies(float dt);
    // mais classes conforme necessário
private:
    bool game_over;
    std::list<Enemy> _enemies;
    std::list<Point> _initial_positions;
    float _last_spawn;
    float crt_time;
}

__END_API