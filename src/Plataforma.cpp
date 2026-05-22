#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Plataforma.h"

TrabalhoJogo::Entidades::Obstaculos::Plataforma::Plataforma(float l, int a): largura(l), altura(a)
{
    danoso=false;
}
TrabalhoJogo::Entidades::Obstaculos::Plataforma::~Plataforma()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::executar()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::salvar()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::mover()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::obstaculizar(Jogador* p)
{}