#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;

Inimigo::Inimigo(): 
    Personagem(),
    coolDownAtaque(0.0f),
    directionMove(false),
    nivel_maldade(1)
{}

Inimigo::~Inimigo()
{
    nivel_maldade = -1;
}
void Inimigo::salvarDataBuffer()
{
    Personagem::salvarDataBuffer();
    
    if (buffer != nullptr)
    {
        *buffer << to_string(nivel_maldade) << ' ';
    }
}

void Inimigo::tentarDanificar(Jogador* pJ)
{
    if (clockAtaque.getElapsedTime().asSeconds() >= cooldownAtaque)
    {
        danificar(pJ);
        clockAtaque.restart();
    }
}

void Inimigo::danificar(Jogador* pJ)
{
    pJ->sofrerAtaque(nivel_maldade/2);
}                  

void Inimigo::sofrerAtaque(int dano)
{
    num_vidas-=dano;
}