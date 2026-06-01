#include "../include/Entidade.h"
#include "../include/Jogador.h"
#include "../include/Plataforma.h"
#include "../include/Gerenciador_Colisoes.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;
using namespace Gerenciadores;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;


Gerenciador_Colisoes::Gerenciador_Colisoes(Jogador* pJ, Plataforma* pP): 
    pAnakin(pJ), 
    pPlat(pP)
{}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{}

bool Gerenciador_Colisoes::executar()
{
    //estou sempre caindo aqui, portanto aqui chamo todas as verificações necessárias
    //talvez compense cair em outro lugar tbm esse bool tá sendo usado para "desativar" a gravidade quando estiver no solo

    if(verificarColisao(static_cast<Entidade*>(pAnakin),static_cast<Entidade*>(pPlat)))
        tratarColisoesJogsObstaculos();

    return caracterOutOfBounds(static_cast<Entidade*>(pAnakin));
}
const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    if ((pe1->getBounds()).intersects(pe2->getBounds()))
        return true;
    return false;
}
void Gerenciador_Colisoes::tratarColisoesJogsObstaculos() //AQUI NÃO ESTÁ FUNCIONANDO
{
    
    sf::FloatRect playerBounds = pAnakin->getBounds();
    sf::FloatRect platBounds = pPlat->getBounds();
    
    if 
    (
        ((pAnakin->getX()) > (pPlat->getX() - platBounds.width))
        &&
        ((pAnakin->getX()) < (pPlat->getX() + platBounds.width))
    )
    {
        bool upDown = 0;
        if ((pAnakin->getY() - playerBounds.height) < (pPlat->getY() - platBounds.height))
            upDown=1;  
        if (upDown)
            pAnakin->setY(pAnakin->getY() - 2);
        else
            pAnakin->setY(pAnakin->getY() + 2);        
    }
   
    else     
    {
        cout<<"oi 2"<<endl;
        
        bool rightLeft = 0;
        if ((pAnakin->getX() - playerBounds.width) > (pPlat->getX() + (platBounds.width / 2.0f)))
            rightLeft=1;

        if (rightLeft)
            pAnakin->setX(pAnakin->getX() + 2);
        else
            pAnakin->setX(pAnakin->getX() - 2);
    }
    
}
void Gerenciador_Colisoes::tratarColisoesJogsInimigos()
{
    
}
void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{
    
}
bool Gerenciador_Colisoes::caracterOutOfBounds(Entidade* pe)
{
    sf::FloatRect playerPosition = pe->getBounds();
    
    if(playerPosition.top <= 0)
        pe->setY(pe->getY() + 2);
    if(playerPosition.top + playerPosition.height >= 710)
        pe->setY(pe->getY() - 2);
    if(playerPosition.left <= 0)
        pe->setX(pe->getX() + 2);
    if(playerPosition.left + playerPosition.width >= 1280)
        pe->setX(pe->getX() - 2);
    
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