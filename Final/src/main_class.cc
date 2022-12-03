#include "main_class.h"

__BEGIN_API
void Main::run(void *name)
{

    srand(time(0));

    Engine shooty(800, 600, 60);
    shooty.init();
    shooty.run();
}
__END_API
