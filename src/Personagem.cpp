#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

#include "../include/Personagem.h"

TrabalhoJogo::Entidades::Personagens::Personagem::Personagem(): Entidade(), num_vidas(0)
{

}

TrabalhoJogo::Entidades::Personagens::Personagem::~Personagem()
{
    
}

void TrabalhoJogo::Entidades::Personagens::Personagem::salvarDataBuffer()
{
    
}

void TrabalhoJogo::Entidades::Personagens::Personagem::gravity()
{
    y+=1;
}