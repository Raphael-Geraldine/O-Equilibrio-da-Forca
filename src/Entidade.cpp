#include "limits.h"
#include"../include/Ente.h"
#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

const float Entidade::velocidadeMaxQueda (900.0f);
const float Entidade::pixelsPorMetro (50.0f);
const float Entidade::gravidadeReal (9.8f);
const float Entidade::gravidade (gravidadeReal * pixelsPorMetro);

Entidade::Entidade(): Ente(), x(0), y(0), velocidade(0.0f, 0.0f), dt(1.0f/ 60.0f), noChao(false)
{}

Entidade::~Entidade()
{
    x = INT_MIN;
    y = INT_MIN;
}

void Entidade::gravity()
{
    if (!noChao)
    {
        // v = v0 + gt;
        // y > 0 para baixo.
        velocidade.y += gravidade * dt;

        if (velocidade.y > velocidadeMaxQueda) 
            velocidade.y = velocidadeMaxQueda;
    }
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