/**
 * @file main.cc
 * @brief
 *
 */

#include "thread.h"
#include "system.h"
#include "main_class.h"

__USING_API

int main(void)
{
    // Main::start_allegro(800, 600, 60);
    System::init(&Main::run);
    std::cout << "voltei a main.cc" << std::endl;
}
