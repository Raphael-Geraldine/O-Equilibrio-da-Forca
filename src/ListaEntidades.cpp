#pragma once

#include "../include/ListaEntidades.h"
using namespace TrabalhoJogo; 
using namespace Listas;

ListaEntidades::ListaEntidades() 
{}

ListaEntidades::~ListaEntidades() 
{
    LEs.limpar();
}

void ListaEntidades::incluir(Entidades::Entidade* pE) 
{
    if (pE == NULL) 
         cerr << "Ponteiro de entidade nulo! Nao incluido!" << endl;

    else 
        LEs.incluir(pE);
}

void ListaEntidades::remover(Entidades::Entidade* pE) 
{
    if (pE == NULL) 
         cerr << "Ponteiro para o qual se solicita remocao (por informacao) eh nulo!" << endl;

    else 
        LEs.remover(pE);
}

void ListaEntidades::remover(size_t indice) 
{
    LEs.remover(indice);
}

size_t ListaEntidades::getTamanho() 
{
    LEs.getTamanho();
}

void ListaEntidades::percorrer() 
{
    // À implementar.
}

Entidades::Entidade* ListaEntidades::operator[](int indice) 
{
    return LEs[indice];
}