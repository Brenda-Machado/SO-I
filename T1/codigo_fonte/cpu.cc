#include "cpu.h"
#include <iostream>
#include "ucontext.h" //arquivo com os metodos context

__BEGIN_API

void CPU::Context::save()
{
    //adicionar implementação
    //salvar na pilha - alocar
    //int setcontext(const ucontext_t *);
}

void CPU::Context::load()
{
    //adicionar implementação
    //carregar da pilha - desalocar
    //int getcontext(ucontext_t *);
}

CPU::Context::~Context()
{
    //adicionar implementação
    //destroi contexto - libera a memoria alocada na pilha
}

void CPU::switch_context(Context *from, Context *to)
{
     //implementação do método
     //troca contextos - swapContext
     //int swapcontext(Context *from, Context *to);
}

__END_API
