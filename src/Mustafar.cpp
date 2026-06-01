#include "../include/Mustafar.h"
#include "../include/Fase.h"
#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Fases;
using namespace Entidades;
using namespace Personagens;

Mustafar::Mustafar(Jogador* pJ1, Jogador* pJ2): 
    Fase(pJ1, pJ2),
    minInimigosMedios(3),
    maxInimigosMedios(10)
{
    criarObstaculos();
    criarInimigos();
}

Mustafar::~Mustafar()
{
    
}

void Mustafar::criarInimigos()
{
    
}

void Mustafar::criarObstaculos()
{
    
}
