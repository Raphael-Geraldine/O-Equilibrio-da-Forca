#include "../include/Entidade.h"
#include "../include/Personagem.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include <iostream>
using namespace std;

const float Personagem::velocidadePulo = -370.0f; //alterei de -420.0f para 370.0f, com "bônus de altura no chão"

Personagem::Personagem(): 
    Entidade(), 
    num_vidas(0)
    // 1 segundo / 60 frames = 0,16666... segundos por frame
{

}

Personagem::~Personagem()
{
    
}

/*
void Personagem::atualizarPosicao() 
{
    dt = relogio.getElapsedTime().asSeconds();
    float ds = velFinal.x * dt;
    if (paraEsquerda) {
        ds *= -1;
    }

    corpo.move(ds, 0.0f);
}
*/

void Personagem::salvarDataBuffer()
{
    
}

int Personagem::getVida()
{
    return num_vidas;
}

void Personagem::setNoChao(const bool emChao)
{
    noChao = emChao;
}

bool Personagem::getNoChao() const 
{
    return noChao;
}

void Personagem::salvarPosicaoAnterior()
{
    posicaoAnterior.x = x;
    posicaoAnterior.y = y;
}

sf::Vector2f Personagem::getPosicaoAnterior() const
{
    return posicaoAnterior;
}

void Personagem::pular() 
{
    bool plataformaFixa = false;

    if (y + (getBounds().height/2.0f) > 705)
        plataformaFixa = true;
    if (noChao) 
    {
        if (plataformaFixa)
        {
            velocidade.y = velocidadePulo-110; // negativo aumenta em y
            noChao = false;
        }
        else
        {
            velocidade.y = velocidadePulo;
            noChao = false;
        }
    }
}