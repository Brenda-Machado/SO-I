#include "thread.h"

__BEGIN_API

// Inicializando atributos estaticos

int Thread::_last_id = 0;
Thread *Thread::_running = nullptr;
Thread Thread::_main;
CPU::Context Thread::_main_context;
Thread Thread::_dispatcher;
Ordered_List<Thread> Thread::_ready;
Ordered_List<Thread> Thread::_suspended;
Ordered_List<Thread> Thread::_waiting;

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
	return CPU::switch_context(prev->context(), next->context());
}

/*
 * Termina a thread.
 * exit_code é o código de término devolvido pela tarefa.
 * Quando a thread encerra, o controle deve retornar à main.
 */
void Thread::thread_exit(int exit_code)
{
	db<Thread>(TRC) << "Thread::thread_exit()\n";

	_state = FINISHING;
	_ready.insert(&_link);
	_running = &_dispatcher;
	_dispatcher._state = RUNNING;
	_ready.remove(&_dispatcher._link);
	if (this->called_join != nullptr)
	{
		this->called_join->resume();
	}
	this->_exit_code = exit_code;
	yield();
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
	int size = _ready.size();
	while (size > 0)
	{
		Thread *next = _ready.head()->object();
		_ready.remove_head();

		_dispatcher._state = READY;
		_ready.insert(&_dispatcher._link);
		_running = next;
		_running->_state = RUNNING;

		switch_context(&_dispatcher, _running);
		if (next->_state == FINISHING)
		{
			_ready.remove(next);
		}

		size = _ready.size();
	}
	_dispatcher._state = FINISHING;
	yield();
}

/*
 * NOVO MÉTODO DESTE TRABALHO.
 * Realiza a inicialização da class Thread.
 * Cria as Threads main e dispatcher.
 */
void Thread::init(void (*main)(void *))
{
	db<Thread>(TRC) << "Thread::init()\n";
	std::string nome = "main";
	new (&_main) Thread((void (*)(char *))main, (char *)nome.data());
	_main_context = CPU::Context();
	_main_context.save();
	new (&_dispatcher) Thread(Thread::dispatcher);

	_running = &_main;
	_main._state = RUNNING;
	_ready.remove(&_main._link);
	CPU::switch_context(&_main_context, _main.context());
}

/*
 * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
 * para ser executada.
 */
void Thread::yield()
{
	db<Thread>(TRC) << "Thread::yield()\n";
	_ready.remove(&_dispatcher);

	int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	if (_running->_state != FINISHING and _running != &_main)
	{
		_running->_link.rank(now);
	}

	_running->_state = READY;
	if (_running != &_main)
	{
		_ready.insert(&_running->_link);
	}
	Thread *tempptr = _running;
	_running = &_dispatcher;
	_running->_state = RUNNING;
	switch_context(tempptr, _running);
};

Thread::~Thread()
{
	db<Thread>(TRC) << "Thread::~Thread()\n";
	delete this->_context;
}

int Thread::join()
{
	db<Thread>(TRC) << "Thread::join()\n";
	if (this->_state == FINISHING)
	{
		return _exit_code;
	}
	this->called_join = _running;
	_running->suspend();
	Thread *tempptr = _running;
	this->_state = RUNNING;
	_running = this;
	_ready.remove(&this->_link);
	yield();
	return this->_exit_code;
}

void Thread::suspend()
{
	db<Thread>(TRC) << "Thread::suspend()\n";
	_ready.remove(&_link);
	this->_state = SUSPENDED;
	_suspended.insert(&_link);
	yield();
}

void Thread::resume()
{
	db<Thread>(TRC) << "Thread::resume()\n";
	_suspended.remove(&this->_link);
	this->_state = READY;
	_ready.insert(&this->_link);
}

__END_API
