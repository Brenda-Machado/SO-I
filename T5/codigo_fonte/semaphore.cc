#include "semaphore.h"
#include "thread.h"

__BEGIN_API

Ordered_List<Semaphore> Semaphore::_waiting;

/*
    * Construtor do semáforo.
    * Inicializa o atributo _value com o valor passado como parâmetro.
    */
Semaphore::Semaphore(int v) {
    _value = v;
}

/*
    * Destrutor do semáforo.
    * Deve liberar a memória alocada para a fila de threads bloqueadas.
    */
Semaphore::~Semaphore() {  
    delete Thread::_waiting;
}

/*
    * Método para decrementar o valor do semáforo.
    * Se o valor do semáforo for menor ou igual a zero, a thread que chamou o método
    * deve ser bloqueada.
    */
void Semaphore::p()
{
    if (fdec(_value) <= 0) {
        sleep();
    }
}

/*
    * Método para incrementar o valor do semáforo.
    * Se o valor do semáforo for maior que zero, uma thread deve ser desbloqueada.
    */
void Semaphore::v()
{
    if (finc(_value) > 0) {
        wakeup();
    }
}

// THREAD OPERATIONS

/*
    * Método para bloquear a thread que o chamou.
    * A thread deve ser colocada na fila de threads bloqueadas.
    */
void Semaphore::sleep() {
    Thread::sleep_running();
}

/*
    * Método para desbloquear uma thread.
    * A thread deve ser removida da fila de threads bloqueadas.
    */
void Semaphore::wakeup() {
    Thread::wakeup_waiting();
}

/* 
    * Método para desbloquear todas as threads.
    */
void Semaphore::wakeup_all() {
    while (!Thread::_waiting.empty()) {
       wakeup();
    }
}

__END_API