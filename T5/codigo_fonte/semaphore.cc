#include "semaphore.h"
#include "thread.h"

__BEGIN_API

/*
    * Construtor do semáforo.
    * Inicializa o atributo _value com o valor passado como parâmetro.
    * Inicializa a fila de threads bloqueadas.
    */
Semaphore::Semaphore(int v) {
    _value = v;
    _blocked = new Thread::Waiting_Queue();
}

/*
    * Destrutor do semáforo.
    * Deve liberar a memória alocada para a fila de threads bloqueadas.
    */
Semaphore::~Semaphore() {  
    delete _blocked;
}

/*
    * Método para decrementar o valor do semáforo.
    * Se o valor do semáforo for menor ou igual a zero, a thread que chamou o método
    * deve ser bloqueada.
    * Caso contrário, o valor do semáforo deve ser decrementado.
    */
void Semaphore::p()
{
    if (fdec(_value) <= 0) {
        sleep()
    } else {
        _value--;
    }
}

/*
    * Método para incrementar o valor do semáforo.
    * Se o valor do semáforo for maior que zero, uma thread deve ser desbloqueada.
    * Caso contrário, o valor do semáforo deve ser incrementado.
    */
void Semaphore::v()
{
    if (finc(_value) > 0) {
        wakeup();
        _value++;
    }
}

// THREAD OPERATIONS

/*
    * Método para bloquear a thread que o chamou.
    * A thread deve ser colocada na fila de threads bloqueadas.
    * Deve ser chamado pelo método p() do semáforo.
    */
void Semaphore::sleep() {
    Thread::running()->state(Thread::WAITING);
    _blocked->insert(Thread::running());
    Thread::yield();
}

/*
    * Método para desbloquear uma thread.
    * A thread deve ser removida da fila de threads bloqueadas.
    * Deve ser chamado pelo método v() do semáforo.
    */
void Semaphore::wakeup() {
    Thread *t = _blocked->remove()->object();
    t->state(Thread::READY);
    Thread::ready()->insert(t);
}

/* 
    * Método para desbloquear todas as threads.
    */
void Semaphore::wakeup_all() {
    while (!_blocked->empty()) {
        Thread *t = _blocked->remove()->object();
        t->state(Thread::READY);
        Thread::ready()->insert(t);
    }
}

__END_API