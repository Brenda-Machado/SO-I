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
        Thread::running()->state(Thread::WAITING);
        _blocked->insert(Thread::running());
        Thread::yield();
    } else {
        _value--;
    }
}

/*
    * Método para incrementar o valor do semáforo.
    * Se o valor do semáforo for menor que zero, uma thread deve ser desbloqueada.
    * Caso contrário, o valor do semáforo deve ser incrementado.
    */
void Semaphore::v()
{
    if (finc(_value) < 0) {
        Thread *t = _blocked->remove()->object();
        t->state(Thread::READY);
        Thread::ready()->insert(t);
    } else {
        _value++;
    }
}


__END_API