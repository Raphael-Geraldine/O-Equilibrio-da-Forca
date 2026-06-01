#include "limits.h"
#include"../include/Ente.h"
#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

Entidade::Entidade(): Ente(), x(0), y(0)
{}

Entidade::~Entidade()
{
    x = INT_MIN;
    y = INT_MIN;
}

void Entidade::salvarDataBuffer()
{
    
}

void Entidade::setX(int i) 
{
    x = i;
}

int Entidade::getX() const
{
    return x;
}

void Entidade::setY(int j) 
{
    y = j;
}

int Entidade::getY() const 
{
    return y;
}