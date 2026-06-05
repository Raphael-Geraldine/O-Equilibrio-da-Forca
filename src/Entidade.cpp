#include "limits.h"
#include"../include/Ente.h"
#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

Entidade::Entidade(ID identificador): Ente(), x(0), y(0), id(identificador)
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

float Entidade::getX() const
{
    return x;
}

void Entidade::setY(int j) 
{
    y = j;
}

float Entidade::getY() const 
{
    return y;
}

int Entidade::getID() const
{
    return id;
}