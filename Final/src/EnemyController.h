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

#include <string>
#include "Vector.h"
#include "list.h"
#include "Point.h"
#include "Enemy.h"
#include "Sprite.h"
#include "time.h"

class EnemyController
{
public:
    typedef List<Enemy> EnemyList;

    EnemyController();
    ~EnemyController();
    void start();
    void spawn_enemies(int number_enemies);
    void update_enemies(float dt);
    // mais classes conforme necessário
private:
    bool game_over;
    EnemyList enemies;
}
