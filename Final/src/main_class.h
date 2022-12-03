#ifndef main_class_h
#define main_class_h

#include <iostream>
#include "traits.h"
#include "Engine.h"
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>

__BEGIN_API

class Main
{
public:
    Main()
    {
    }

    static void run(void *name);

    ~Main() {}

private:
};

__END_API

#endif
