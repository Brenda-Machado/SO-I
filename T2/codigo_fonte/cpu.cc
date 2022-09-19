#include "cpu.h"
#include <iostream>
#include <ucontext.h>

__BEGIN_API

void CPU::Context::save()
{
    getcontext(&_context);
}

void CPU::Context::load()
{
    setcontext(&_context);
}

CPU::Context::~Context()
{   
    if (_stack)
        delete[] _stack;
}

void CPU::switch_context(Context *from, Context *to)
{
    swapcontext(&(from->_context), &(to->_context));
}

__END_API
