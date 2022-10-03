#include "thread.h"

__BEGIN_API

// Inicializando atributos estaticos

int Thread::_last_id = 0;
Thread * Thread::_running = nullptr;

/*
 * Retorna o ID da thread.
 */ 
int Thread::id(){
	db<Thread>(TRC) << "Thread::id()\n";
	return _id;
}

// Retornar contexto da thread
Thread::Context* Thread::context(){
	db<Thread>(TRC) << "Thread::context()\n";
	return _context;
}

/*
 * Método para trocar o contexto entre duas thread, a anterior (prev)
 * e a próxima (next).
 * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
 * Valor de retorno é negativo se houve erro, ou zero.
 */ 
int Thread::switch_context(Thread * prev, Thread * next){
	db<Thread>(TRC) << "Thread::switch_context()\n";
	_running = next;
	CPU::switch_context(prev->context(), next->context());
	return 0;
}


// Constutor vazio para criar thread main
/*
Thread::Thread(){
	_context = new Context();
	_id = _last_id++;
}
*/

/*
 * Termina a thread.
 * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
 * Quando a thread encerra, o controle deve retornar à main. 
 */  
void Thread::thread_exit (int exit_code){
	db<Thread>(TRC) << "Thread::thread_exit()\n";
	delete _context;
}
__END_API
