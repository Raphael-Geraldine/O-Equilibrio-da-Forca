#include "../include/Fase.h"
using namespace TrabalhoJogo;
using namespace Fases;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Mustafar.h"

TrabalhoJogo::Fases::Mustafar::Mustafar(Jogador* pJ): Fase(pJ), minInimigosMedios(3), maxInimigosMedios(10)
{
    criarObstaculos();
    criarInimigos();
}

TrabalhoJogo::Fases::Mustafar::~Mustafar()
{
    
}

void TrabalhoJogo::Fases::Mustafar::criarInimigos()
{
    
}

void TrabalhoJogo::Fases::Mustafar::criarObstaculos()
{
    
}