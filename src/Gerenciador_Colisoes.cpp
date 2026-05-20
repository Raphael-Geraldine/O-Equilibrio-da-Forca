#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include <iostream>
using namespace std;

#include "../include/Gerenciador_Colisoes.h"

TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::Gerenciador_Colisoes(Jogador* pJ)
{
    pAnakin=pJ;
}
TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::~Gerenciador_Colisoes()
{

}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::executar()
{
    //estou sempre caindo aqui, portanto aqui chamotodas as verificações necessárias
    caracterOutOfBounds(static_cast<Entidade*>(pAnakin));
}
const bool TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsObstaculos()
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsInimigos()
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::caracterOutOfBounds(Entidade* pe)
{
    //IMPLEMENTAR AQUI A LÓGICA PARA NÃO SAIR DA TELA
}

/* void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::incluirInimigo(Inimigo* pi)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::incluirObstaculo(Obstaculo* po)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::incluirProjetil(Projetil* pj)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::setJog1(Jogador* pJ)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::setJog2(Jogador* pJ)
{
    
}*/