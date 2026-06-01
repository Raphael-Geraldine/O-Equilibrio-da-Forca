#include "../include/ListaEntidades.h"
using namespace TrabalhoJogo; 
using namespace Listas;

#include <iostream> 
using std::cout;
using std::cerr;
using std::endl;

ListaEntidades::ListaEntidades() 
{}

ListaEntidades::~ListaEntidades() 
{
    limpar();
}

void ListaEntidades::limpar()
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

size_t ListaEntidades::getTamanho() const
{
    return LEs.getTamanho();
}

Entidades::Entidade* ListaEntidades::operator[](int indice) 
{
    return LEs[indice];
}

// Lista elemento por elemento (template).
void ListaEntidades::percorrer() 
{
    LEs.percorrer();
}

// Chama executar de cada Entidade.
void ListaEntidades::executar() 
{
    int tamanho = static_cast<int>(getTamanho());
    for (int i = 0; i < tamanho; i++)
    {
        LEs[i]->executar();
    }
}