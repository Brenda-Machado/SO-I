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
    static void start(EnemyController *enemy_controller);
    void run();
    void addEnemy(Enemy *enemy);
    void removeEnemy(Enemy *enemy);
    void init();
    void spawn_enemies();
    void update_enemies(float dt);
    static void end() {};
    // mais classes conforme necessário
private:
    bool game_over;
    std::list<Enemy> _enemies;
    std::list<Point> _initial_positions;
    float _last_spawn;
    float _crt_time;
};

__END_API