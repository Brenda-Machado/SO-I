#ifndef semaphore_h
#define semaphore_h

#include "cpu.h"
#include "thread.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class Semaphore
{
public:
    typedef Ordered_List<Thread> Waiting_Queue;
    Semaphore(int v = 1);
    ~Semaphore();

    void p();
    void v();

private:
    // Atomic operations
    int finc(volatile int &number);
    int fdec(volatile int &number);

    // Thread operations
    void sleep();
    void wakeup();
    void wakeup_all();

private:
    // DECLARAÇÃO DOS ATRIBUTOS DO SEMÁFORO
    volatile int _value;
    Waiting_Queue *_waiting;
};

__END_API

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 6ff5be0b54e900d59412899dc9b6650953f559db
