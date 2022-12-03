// /**
//  * @file Engine.h
//  * @brief
//  *
//  * @author
//  * @bug
//  */
// #ifndef WINDOW_H
// #define WINDOW_H

// #include <allegro5/allegro.h>
// #include <memory>
// #include <string>

// #include "Sprite.h"
// #include "Vector.h"
// #include "Action.h"

// class Window
// {
// public:
//     Window(int w, int h, int fps, ALLEGRO_DISPLAY *display);
//     ~Window();

//     void init();
//     void run();
//     void draw();
//     void loadSprites();
//     inline int getWidth() const
//     {
//         return _displayWidth;
//     }
//     inline int getHeight() const
//     {
//         return _displayHeight;
//     }
//     inline int getFps() const
//     {
//         return _fps;
//     }

// private:
//     // Background
//     Point bgMid; /**<point used by the background to draw from */
//     Point fgMid;
//     Point fg2Mid;
//     Vector bgSpeed; /**<background movement speed */
//     Vector fgSpeed;
//     std::shared_ptr<Sprite> bg; /**<shared pointer to background animation */
//     std::shared_ptr<Sprite> fg;

//     // general game variables
//     int _displayWidth;
//     int _displayHeight;
//     int _fps;

//     // allegro objects
//     ALLEGRO_TIMER *_timer;
//     ALLEGRO_DISPLAY *_display;
// };

// #endif