#include "cpu.h"
#include <iostream>
#include "ucontext.h" //arquivo com os metodos context

__BEGIN_API

void CPU::Context::save()
{
    //adicionar implementação
    //salvar na pilha - setContext
}

void CPU::Context::load()
{
    //adicionar implementação
    //carregar da pilha - getContext
}

CPU::Context::~Context()
{
    //adicionar implementação
    //cria contexto - makeContext
}

void CPU::switch_context(Context *from, Context *to)
{
     //implementação do método
     //troca contextos - swapContext
}

__END_API
