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
    std::cout << "~Context" << std::endl;
    if (_stack)
        delete[] _stack;
    std::cout << "~Context end" << std::endl;
}

int CPU::switch_context(Context *from, Context *to)
{
    // std::cout << "switching from " << from << " to " << to << std::endl;
    return swapcontext(&(from->_context), &(to->_context));
}

__END_API
