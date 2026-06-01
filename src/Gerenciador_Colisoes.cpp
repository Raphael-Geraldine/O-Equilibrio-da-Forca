#include "../include/Gerenciador_Colisoes.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Listas;
using namespace Personagens;
using namespace Obstaculos;
using namespace Gerenciadores;


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;


Gerenciador_Colisoes::Gerenciador_Colisoes(ListaEntidades* pLE): 
    pListaEntidades(pLE)
{}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{}

void Gerenciador_Colisoes::tratarColisoesJogsObstaculos(Jogador* pJog, Plataforma* pPlat) //AQUI NÃO ESTÁ FUNCIONANDO
{
    if (pJog == nullptr || pPlat == nullptr)
        return;
    
    sf::FloatRect playerBounds = pJog->getBounds();
    sf::FloatRect platBounds = pPlat->getBounds();
    
    const int RECUO_COLISAO = 2;

    if (((pJog->getX() - playerBounds.width) > (pPlat->getX() - platBounds.width)) 
       && ((pJog->getX() + playerBounds.width) < (pPlat->getX() + platBounds.width)))
    {
        bool upDown = false;

        if ((pJog->getY() - playerBounds.height) < (pPlat->getY() - platBounds.height))
            upDown=true;

        if (upDown)
            pJog->setY(pJog->getY() - RECUO_COLISAO);
        
        else
            pJog->setY(pJog->getY() + RECUO_COLISAO);        
    }
   
    else     
    {
        bool rightLeft = false;
        
        if ((pJog->getX() + playerBounds.width) > (pPlat->getX() + platBounds.width / 2.0f))
            rightLeft = true;

        if (rightLeft)
            pJog->setX(pJog->getX() + RECUO_COLISAO);

        else
            pJog->setX(pJog->getX() - RECUO_COLISAO);
    }
    
}

bool Gerenciador_Colisoes::executar()
{
    //estou sempre caindo aqui, portanto aqui chamo todas as verificações necessárias
    //talvez compense cair em outro lugar tbm esse bool tá sendo usado para "desativar" a gravidade quando estiver no solo
    if (pListaEntidades == nullptr)
    {
        cerr << "Erro: lista de entidades nula no Gerenciador de Colisoes." << endl;
        return false;
    }

    bool aplicarGravidade = false;

    int tamanho = static_cast<int>(pListaEntidades->getTamanho());

    for (int i = 0; i < tamanho; i++) 
    {
        if ((*pListaEntidades)[i] == nullptr)
            continue; // Ou não deve ser tolerado:

        else 
        {
            Jogador* pJog = dynamic_cast<Jogador*>((*pListaEntidades)[i]);

            if (pJog != nullptr) 
            {
                aplicarGravidade = caracterOutOfBounds(pJog);

                for (int j = 0; j < tamanho; j++) 
                {
                    if (i == j)
                        continue;
                    
                    Entidade* pEnt2 = (*pListaEntidades)[j];

                    if (pEnt2 == nullptr)
                        continue;

                    Plataforma* pPlat = dynamic_cast<Plataforma*>(pEnt2);

                    if (pPlat != nullptr) 
                    {
                        if(verificarColisao(pJog, pPlat)) 
                        {
                            tratarColisoesJogsObstaculos(pJog, pPlat);
                            aplicarGravidade = false;
                        }
                    }
                }
            }
        }
    }
    return aplicarGravidade;
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    if ((pe1->getBounds()).intersects(pe2->getBounds()))
        return true;
    return false;
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
        return true;

    return false;
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