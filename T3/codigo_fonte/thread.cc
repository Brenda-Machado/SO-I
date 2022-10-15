#include "thread.h"

__BEGIN_API

// Inicializando atributos estaticos

int Thread::_last_id = 0;
Thread *Thread::_running = nullptr;

/*
 * Retorna o ID da thread.
 */
int Thread::id()
{
	db<Thread>(TRC) << "Thread::id()\n";
	return _id;
}

// Retornar contexto da thread
Thread::Context *Thread::context()
{
	db<Thread>(TRC) << "Thread::context()\n";
	return _context;
}

/*
 * Método para trocar o contexto entre duas thread, a anterior (prev)
 * e a próxima (next).
 * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
 * Valor de retorno é negativo se houve erro, ou zero.
 */
int Thread::switch_context(Thread *prev, Thread *next)
{
	db<Thread>(TRC) << "Thread::switch_context()\n";
	_running = next;
	if (!CPU::switch_context(prev->context(), next->context()))
	{
		return 0;
	}
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
 * exit_code é o código de término devolvido pela tarefa.
 * Quando a thread encerra, o controle deve retornar à main.
 */
void Thread::thread_exit(int exit_code)
{
	db<Thread>(TRC) << "Thread::thread_exit()\n";
	if (exit_code != 0) {
		this->_state = FINISHING;
		this->switch_context(this, &_main);
		delete this->_context;
	}
}
/*
 * NOVO MÉTODO DESTE TRABALHO.
 * Daspachante (disptacher) de threads.
 * Executa enquanto houverem threads do usuário.
 * Chama o escalonador para definir a próxima tarefa a ser executada.
 */
void Thread::dispatcher()
{
	db<Thread>(TRC) << "Thread::dispatcher()\n";
	while (true)
	{ // enquanto existir thread do usuário
		Thread *next = _ready.head()->object();
		_dispatcher._state = READY;
		_ready.insert(&_dispatcher._link);
		_running = next;
		_running->_state = RUNNING;
		switch_context(_running, next);
		if (next->_state == FINISHING)
		{
			_ready.remove(next);
		}
	}
	_dispatcher._state = FINISHING;
	_ready.remove(&_dispatcher);
	switch_context(&_dispatcher, &_main);
}

/*
 * NOVO MÉTODO DESTE TRABALHO.
 * Realiza a inicialização da class Thread.
 * Cria as Threads main e dispatcher.
 */
void Thread::init(void (*main)(void *))
{
	db<Thread>(TRC) << "Thread::init()\n";
	_main = Thread((void (*)())main);

	_main._context = new Context(main);
	_main._id = _last_id++;
	_running = &_main;
	_dispatcher._context = new Context(&dispatcher);
}

/*
 * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
 * para ser executada.
 */
void Thread::yield()
{
	db<Thread>(TRC) << "Thread::yield()\n";
	Thread *next = _ready.head()->object();
	int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	if (next->_state != FINISHING and next != &_main)
	{
		this->_link.rank() = now;
	}
	
	_ready.insert(&_running->_link);
	_running = next;
	_running->_state = RUNNING;
	switch_context(_running, next);
};

__END_API
