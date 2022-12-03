// #include "Window.h"

// #include <allegro5/allegro_primitives.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_audio.h>
// #include <allegro5/allegro_acodec.h>
// #include <stdexcept>
// #include <iostream>

// #include "Timer.h"

// Window::Window(int w, int h, int fps, ALLEGRO_DISPLAY *display) : _displayWidth(w),
//                                                                   _displayHeight(h),
//                                                                   _fps(fps),
//                                                                   _display(display)
// {
// }

// void Window::init()
// {
//     loadSprites();
// }

// void loadSprites()
// {

//     // Create Ship
//     centre = Point(215, 245);
//     color = al_map_rgb(0, 200, 0);

//     // represents the middle of the image width-wise, and top height-wise
//     bgMid = Point(0, 0);
//     fgMid = Point(800, 0);
//     fg2Mid = Point(300, 300);
//     bgSpeed = Vector(50, 0);
//     fgSpeed = Vector(-90, 0);

//     // Go to resources directory
//     ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
//     al_append_path_component(path, "resources");
//     al_change_directory(al_path_cstr(path, '/'));
//     // sprites
//     spaceShip = std::make_shared<Sprite>("Sprite2.png"); // espaçonave do usuário
//     bg = std::make_shared<Sprite>("BGstars.png");        // fundo da tela - background
//     // delete path
//     al_destroy_path(path);
// }