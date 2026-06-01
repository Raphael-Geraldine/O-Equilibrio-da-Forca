#include "../include/Entidade.h"
#include "../include/Personagem.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

Personagem::Personagem(): Entidade(ID::personagem), num_vidas(0)
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

void Personagem::gravity()
{
    y+=1;
}