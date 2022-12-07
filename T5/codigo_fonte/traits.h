#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API    \
	namespace SOLUTION \
	{
#define __END_API }
#define __USING_API using namespace SOLUTION;

__BEGIN_API

class CPU; // declaração das classes criadas nos trabalhos devem ser colocadas aqui

class Debug;
class System;
class Thread;
class Lists;
class Semaphore;

// declaração da classe Traits
template <typename T>
struct Traits
{
	static const bool debugged = false;
};

template <>
struct Traits<CPU>
{
	static const unsigned int STACK_SIZE = 16000;
	static const bool debugged = true;
};

/*
Essa classe adiciona 4 níveis de debug ao sistema: error (ERR), warning (WRN), info
(INF) e trace (TRC).
db<CLASSE>(NÍVEL) << “mensagem\n”;
*/
template <>
struct Traits<Debug> : public Traits<void>
{
	static const bool error = false;
	static const bool warning = false;
	static const bool info = false;
	static const bool trace = true;
};

template <>
struct Traits<System> : public Traits<void>
{
	static const bool debugged = true;
};

template <>
struct Traits<Thread> : public Traits<void>
{
	static const bool debugged = true;
};

template <>
struct Traits<Lists> : public Traits<void>
{
	static const bool debugged = true;
};

template <>
struct Traits<Semaphore> : public Traits<void>
{
	static const bool debugged = true;
};
__END_API

#endif