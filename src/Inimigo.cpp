#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

Inimigo::Inimigo(): Personagem(inimigo), nivel_maldade(50), cooldownAtaque(1.0f)
{

}
Inimigo::~Inimigo()
{
    nivel_maldade = -1;
}
void Inimigo::salvarDataBuffer()
{

}

void Inimigo::tentarDanificar(Jogador* pJ)
{
    if (clock.getElapsedTime().asSeconds() >= cooldownAtaque)
    {
        danificar(pJ);
        clock.restart();
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