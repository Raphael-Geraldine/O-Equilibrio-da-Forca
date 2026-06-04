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

Gerenciador_Colisoes::Gerenciador_Colisoes(Lista<Jogador>* pLJ, Lista<Obstaculo>* pLO, Lista<Inimigo>* pLI,  sf::RectangleShape* pG): 
    pListaJogadores(pLJ),
    pListaObstaculos(pLO),
    pListaInimigos(pLI),
    pGround(pG)
{

}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
    pListaJogadores = nullptr;
    pListaObstaculos = nullptr;
    pListaInimigos = nullptr;
    pGround = nullptr;
}

void Gerenciador_Colisoes::tratarColisoesJogsObstaculos(Jogador* pJog, Obstaculo* pObs)
{
    if (pJog == nullptr || pObs == nullptr) 
        return;

    pObs->obstaculizar(pJog);
}

void Gerenciador_Colisoes::tratarColisoesInimObstaculos(Inimigo* pInim, Obstaculo* pObs)
{
    if (pInim == nullptr || pObs == nullptr)
        return;
    
    sf::FloatRect inimBounds = pInim->getBounds();
    sf::FloatRect obsBounds = pObs->getBounds();
    
    const int RECUO_COLISAO = 2;

    if (((pInim->getX() - inimBounds.width) > (pObs->getX() - obsBounds.width)) 
       && ((pInim->getX() + inimBounds.width) < (pObs->getX() + obsBounds.width)))
    {
        bool upDown = false;

        if ((pInim->getY() - inimBounds.height) < (pObs->getY() - obsBounds.height))
            upDown=true;

        if (upDown)
            pInim->setY(pInim->getY() - RECUO_COLISAO);
        
        else
            pInim->setY(pInim->getY() + RECUO_COLISAO);        
    }
   
    else     
    {
        bool rightLeft = false;
        
        if ((pInim->getX() + inimBounds.width) > (pObs->getX() + obsBounds.width / 2.0f))
            rightLeft = true;

        if (rightLeft)
            pInim->setX(pInim->getX() + RECUO_COLISAO);

        else
            pInim->setX(pInim->getX() - RECUO_COLISAO);
    }
    
}

void Gerenciador_Colisoes::tratarColisaoJogChao(Jogador* pJog)
{
    if (pJog == nullptr || pGround == nullptr)
        return;

    sf::FloatRect jogBounds = pJog->getBounds();
    sf::FloatRect chaoBounds = pGround->getGlobalBounds();
    sf::FloatRect intersecao;

    if (!jogBounds.intersects(chaoBounds, intersecao))
        return;

    // Só faz sentido o caso do jogador vindo de cima.
    if (jogBounds.top < chaoBounds.top)
    {
        pJog->setY(pJog->getY() - intersecao.height);
        pJog->setVelocidadeY(0.0f);
        pJog->setNoChao(true);
        pJog->atualizarPosicaoSprite();
    }
}

void Gerenciador_Colisoes::executar()
{
    //estou sempre caindo aqui, portanto aqui chamo todas as verificações necessárias
    //talvez compense cair em outro lugar tbm esse bool tá sendo usado para "desativar" a gravidade quando estiver no solo

    if (pListaJogadores == nullptr || pListaObstaculos == nullptr || pListaInimigos == nullptr)
    {
        cerr << "Erro: Uma ou mais lista de derivados de entidades nula no Gerenciador de Colisoes." << endl;
        return;
    }

    const int qtdJogadores = static_cast<int>(pListaJogadores->getTamanho());
    const int qtdObstaculos = static_cast<int>(pListaObstaculos->getTamanho());
    const int qtdInimigos = static_cast<int>(pListaInimigos->getTamanho());

    if (qtdJogadores == 0) 
    {
        cerr << "Erro: lista de jogadores vazia no Gerenciador de Colisoes." << endl;
        return;
    }

    for (int i = 0; i < qtdJogadores; i++) 
    {
        if ((*pListaJogadores)[i] == nullptr)
        {
            cerr << "Jogador nulo encontrado na lista de jogadores." << endl; // Ou não deve ser tolerado com continue?
            continue;
        }

        Jogador* pJog = (*pListaJogadores)[i];

        pJog->setNoChao(false);

        caracterOutOfBounds(pJog);

        for (int j = 0; j < qtdObstaculos; j++) 
        {       
            Obstaculo* pObs = (*pListaObstaculos)[j];

            if (pObs == nullptr) continue;

            if(verificarColisao(pJog, pObs)) 
            {
                tratarColisoesJogsObstaculos(pJog, pObs);
                //aplicarGravidade = false;
            }
        }

        tratarColisaoJogChao(pJog);

        for (int k = 0; k < qtdInimigos; k++) 
        {       
            Inimigo* pInim = (*pListaInimigos)[k];

            if (pInim == nullptr) continue;

            caracterOutOfBounds(pInim);

            if(verificarColisao(pJog, pInim)) 
                tratarColisoesJogsInimigos(pJog, pInim);
        }
    }

    for (int j = 0; j < qtdInimigos; j++)
    {
        if ((*pListaInimigos)[j] == nullptr)
        {
            cerr << "Inimigo nulo encontrado na lista de inimigos." << endl; // Ou não deve ser tolerado com continue?
            continue;
        }

        Inimigo* pInim = (*pListaInimigos)[j];

        for (int k = 0; k < qtdObstaculos; k++)
        {
            Obstaculo* pObs = (*pListaObstaculos)[k];

            if (pObs == nullptr) continue;

            if(verificarColisao(pInim, pObs)) 
            {
                tratarColisoesInimObstaculos(pInim, pObs);
                //aplicarGravidade = false;
            }
        }
    }
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
    if (pe1 == nullptr || pe2 == nullptr)
        return false;

    return (pe1->getBounds()).intersects(pe2->getBounds());
}

void Gerenciador_Colisoes::tratarColisoesJogsInimigos(Jogador* pJog, Inimigo* pInim)
{
    pInim->tentarDanificar(pJog);
    pJog->colidirInimigo(pInim);
}
void Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{
    
}
void Gerenciador_Colisoes::caracterOutOfBounds(Entidade* pe)
{
    if (pe == nullptr) return;

    sf::FloatRect playerPosition = pe->getBounds();
    
    if(playerPosition.top <= 0)
        pe->setY(pe->getY() + 2);

    if(playerPosition.top + playerPosition.height >= 710)
        pe->setY(pe->getY() - 2);

    if(playerPosition.left <= 0)
        pe->setX(pe->getX() + 2);

    if(playerPosition.left + playerPosition.width >= 1280)
        pe->setX(pe->getX() - 2);
    
    //if(playerPosition.top + playerPosition.height < 708)
        //return true;

    //return false;
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