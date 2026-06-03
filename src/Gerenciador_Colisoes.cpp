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


Gerenciador_Colisoes::Gerenciador_Colisoes(Lista<Jogador>* pLJ, Lista<Plataforma>* pLP, Lista<Inimigo>* pLI): 
    pListaJogadores(pLJ),
    pListaPlataformas(pLP),
    pListaInimigos(pLI)
{

}

Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
    pListaJogadores = nullptr;
    pListaPlataformas = nullptr;
    pListaInimigos = nullptr;
}

void Gerenciador_Colisoes::tratarColisoesJogsObstaculos(Jogador* pJog, Plataforma* pPlat)
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

    if (pListaJogadores == nullptr || pListaPlataformas == nullptr || pListaInimigos == nullptr)
    {
        cerr << "Erro: Uma ou mais lista de derivados de entidades nula no Gerenciador de Colisoes." << endl;
        return false;
    }

    bool aplicarGravidade = true;

    const int qtdJogadores = static_cast<int>(pListaJogadores->getTamanho());
    const int qtdPlataformas = static_cast<int>(pListaPlataformas->getTamanho());
    const int qtdInimigos = static_cast<int>(pListaInimigos->getTamanho());

    if (qtdJogadores == 0) 
    {
        cerr << "Erro: lista de jogadores vazia no Gerenciador de Colisoes." << endl;
        return false;
    }

    for (int i = 0; i < qtdJogadores; i++) 
    {
        if ((*pListaJogadores)[i] == nullptr)
        {
            cerr << "Jogador nulo encontrado na lista de jogadores." << endl; // Ou não deve ser tolerado com continue?
            continue;
        }

        Jogador* pJog = (*pListaJogadores)[i];

        aplicarGravidade = caracterOutOfBounds(pJog);

        for (int j = 0; j < qtdPlataformas; j++) 
        {       
            Plataforma* pPlat = (*pListaPlataformas)[j];

            if (pPlat == nullptr) continue;

            if(verificarColisao(pJog, pPlat)) 
            {
                tratarColisoesJogsObstaculos(pJog, pPlat);
                aplicarGravidade = false;
            }
        }

        for (int k = 0; k < qtdInimigos; k++) 
        {       
            Inimigo* pInim = (*pListaInimigos)[k];

            aplicarGravidade = caracterOutOfBounds(pInim);

            if (pInim == nullptr) continue;

            if(verificarColisao(pJog, pInim)) 
                tratarColisoesJogsInimigos(pJog, pInim);
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

void Gerenciador_Colisoes::tratarColisoesJogsInimigos(Jogador* pJog, Inimigo* pInim)
{
    pInim->tentarDanificar(pJog);
    pJog->colidirInimigo(pInim);
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