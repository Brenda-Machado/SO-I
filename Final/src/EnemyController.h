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
    EnemyController(std::list<Enemy*> *enemies) { 
        game_over = false;
        _enemies = enemies;
     };
    ~EnemyController() {};
    static void start(EnemyController *enemy_controller);
    void run();
    void addEnemy(Enemy *enemy);
    void removeEnemy(Enemy *enemy);
    void updateEnemy(Enemy *enemy);
    void spawn_enemies();
    void check_enemies();
    void end() {
        game_over = true;
        _enemies->clear();
    };
    // mais classes conforme necessário
private:

    bool game_over;
    std::list<Enemy*> *_enemies;
    float _last_spawn;
    float _crt_time;
};

__END_API