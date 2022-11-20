#include "semaphore.h"

__BEGIN_API


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
    Thread *temp;
    temp->delete_waiting();
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
    Thread *temp;
    temp->sleep_running();
}

/*
    * Método para desbloquear uma thread.
    * A thread deve ser removida da fila de threads bloqueadas.
    */
void Semaphore::wakeup() {
    Thread *temp;
    temp->wakeup_waiting();
}

/* 
    * Método para desbloquear todas as threads.
    */
void Semaphore::wakeup_all() {
    Thread *temp;
    while (!temp->waiting_empty()) {
        wakeup();
    }
}

__END_API