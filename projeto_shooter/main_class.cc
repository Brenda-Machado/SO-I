#include "main_class.h"
#include "thread.h"

__BEGIN_API
void Main::run(void *name)
{

    // srand(time(0));

    Engine *engine = new Engine(800, 600, 60);
    Thread *engine_thread = new Thread(Engine::start, engine);
    engine_thread->join();
    delete engine;
    delete engine_thread;
    Thread::exit_running(0);
    std::cout << "ended" << std::endl;
    // shooty.init();
    // shooty.run();
}
__END_API
