#include "main_class.h"
#include "thread.h"

__BEGIN_API
void Main::run(void *name)
{

    srand(time(0));

    Window *window = new Window(800, 600, 60);
    Thread *window_thread = new Thread(Window::start, window);
    window_thread->join();
    delete window;
    delete window_thread;
    Thread::exit_running(0);
    std::cout << "ended" << std::endl;
}
__END_API
