#include "semaphore.h"
__BEGIN_API
/*
 * Construtor do semáforo.
 * Inicializa o atributo _value com o valor passado como parâmetro.
 * Inicializa a fila de threads bloqueadas.
 */
Semaphore::Semaphore(int v)
{
    db<Thread>(TRC) << "Semaphore::Semaphore()\n";
    _value = v;
    _waiting = new Waiting_Queue();
}

/*
 * Destrutor do semáforo.
 * Deve liberar a memória alocada para a fila de threads bloqueadas.
 */
Semaphore::~Semaphore()
{
    db<Thread>(TRC) << "Semaphore::~Semaphore()\n";
    wakeup_all();
    delete _waiting;
}

/*
 * Método para decrementar o valor do semáforo.
 * Se o valor do semáforo for menor ou igual a zero, a thread que chamou o método
 * deve ser bloqueada.
 * Caso contrário, o valor do semáforo deve ser decrementado.
 */
void Semaphore::p()
{
    db<Thread>(TRC) << "Semaphore::p()\n";
    if (_value == 0)
    {
        sleep();
        p();
        return;
    }
    fdec(_value);
}

/*
 * Método para incrementar o valor do semáforo.
 * Se o valor do semáforo for maior que zero, uma thread deve ser desbloqueada.
 * Caso contrário, o valor do semáforo deve ser incrementado.
 */
void Semaphore::v()
{
    db<Thread>(TRC) << "Semaphore::v()\n";
    if (_value == 0)
    {
        finc(_value);
        wakeup();
        return;
    }
    finc(_value);
}

// THREAD OPERATIONS

/*
 * Método para bloquear a thread que o chamou.
 * A thread deve ser colocada na fila de threads bloqueadas.
 * Deve ser chamado pelo método p() do semáforo.
 */
void Semaphore::sleep()
{
    db<Thread>(TRC) << "Semaphore::sleep()\n";
    Thread::running()->set_state(Thread::State::WAITING);

    Waiting_Queue::Element link = Waiting_Queue::Element(Thread::running(), (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));

    _waiting->insert(&link);
    Thread::yield();
}

/*
 * Método para desbloquear uma thread.
 * A thread deve ser removida da fila de threads bloqueadas.
 * Deve ser chamado pelo método v() do semáforo.
 */
void Semaphore::wakeup()
{
    db<Thread>(TRC) << "Semaphore::wakeup()\n";
    if (_waiting->size() > 0)
    {
        Thread *t = _waiting->head()->object();
        _waiting->remove_head();

        Thread::wakeup(t);
    }
}

/*
 * Método para desbloquear todas as threads.
 */
void Semaphore::wakeup_all()
{
    db<Thread>(TRC) << "Semaphore::wakeup_all()\n";
    while (!_waiting->empty())
    {
        wakeup();
    }
}

// decrementar _value
int Semaphore::fdec(volatile int &number)
{
    db<Thread>(TRC) << "Semaphore::fdec()\n";
    int b = -1;
    asm volatile("lock xadd %0, %1"
                 : "+r"(b), "+m"(_value));
    return _value;
}
// incrementar _value
int Semaphore::finc(volatile int &number)
{
    db<Thread>(TRC) << "Semaphore::finc()\n";
    int b = 1;
    asm volatile("lock xadd %0, %1"
                 : "+r"(b), "+m"(_value));
    return _value;
}

__END_API