#include "limits.h"
#include"../include/Ente.h"
using namespace TrabalhoJogo;

#include "../include/Entidade.h"

TrabalhoJogo::Entidades::Entidade::Entidade(): Ente(), x(0), y(0)
{

}

TrabalhoJogo::Entidades::Entidade::~Entidade()
{
    x = INT_MIN;
    y = INT_MIN;
}

void TrabalhoJogo::Entidades::Entidade::salvarDataBuffer()
{
    
}

void TrabalhoJogo::Entidades::Entidade::setX(int i) 
{
    x = i;
}

int TrabalhoJogo::Entidades::Entidade::getX() const
{
    return x;
}

void TrabalhoJogo::Entidades::Entidade::setY(int j) 
{
    y = j;
}

int TrabalhoJogo::Entidades::Entidade::getY() const 
{
    return y;
}