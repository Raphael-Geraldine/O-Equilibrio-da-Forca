#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Plataforma.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;

#include <iostream>
using namespace std;

#include "../include/Gerenciador_Colisoes.h"

TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::Gerenciador_Colisoes(Jogador* pJ, Plataforma* pP): pAnakin(pJ), pPlat(pP)
{

}
TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::~Gerenciador_Colisoes()
{

}
bool TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::executar()
{
    //estou sempre caindo aqui, portanto aqui chamo todas as verificações necessárias
    //talvez compense cair em outro lugar tbm esse bool tá sendo usado para "desativar" a gravidade quando estiver no solo

    if(verificarColisao(static_cast<Entidade*>(pAnakin),static_cast<Entidade*>(pPlat)))
        tratarColisoesJogsObstaculos();

    return caracterOutOfBounds(static_cast<Entidade*>(pAnakin));
}
const bool TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    if ((pe1->getBounds()).intersects(pe2->getBounds()))
        return true;
    return false;
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsObstaculos()
{
    
    sf::FloatRect playerBounds = pAnakin->getBounds();
    sf::FloatRect platBounds = pPlat->getBounds();
    
    if 
    (
        ((pAnakin->x) > (pPlat->x - platBounds.width))
        &&
        ((pAnakin->x) < (pPlat->x + platBounds.width))
    )
    {
        bool upDown = 0;
        if ((pAnakin->y - playerBounds.height) < (pPlat->y - platBounds.height))
            upDown=1;  
        if (upDown)
            pAnakin->y -= 2;
        else
            pAnakin->y += 2;        
    }
   
    else     
    {
        cout<<"oi 2"<<endl;
        
        bool rightLeft = 0;
        if ((pAnakin->x - playerBounds.width) > (pPlat->x + (platBounds.width / 2.0f)))
            rightLeft=1;

        if (rightLeft)
            pAnakin->x += 2;
        else
            pAnakin->x -= 2;
    }
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsInimigos()
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{
    
}
bool TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::caracterOutOfBounds(Entidade* pe)
{
    sf::FloatRect playerPosition = pe->getBounds();
    
    if(playerPosition.top <= 0)
        pe->y+=2;
    if(playerPosition.top + playerPosition.height >= 710)
        pe->y-=2;
    if(playerPosition.left <= 0)
        pe->x+=2;
    if(playerPosition.left + playerPosition.width >= 1280)
        pe->x-=2;
    
    if(playerPosition.top + playerPosition.height < 708)
        return 1;
    return 0;
}

/* void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::incluirInimigo(Inimigo* pI)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::incluirObstaculo(Obstaculo* pO)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::incluirProjetil(Projetil* pJ)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::setJog1(Jogador* pJ)
{
    
}
void TrabalhoJogo::Gerenciadores::Gerenciador_Colisoes::setJog2(Jogador* pJ)
{
    
}*/