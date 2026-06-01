#include "../include/Entidade.h"
#include "../include/Personagem.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

Personagem::Personagem(): Entidade(), num_vidas(0)
{

}

Personagem::~Personagem()
{
    
}

void Personagem::salvarDataBuffer()
{
    
}

void Personagem::gravity()
{
    y+=1;
}