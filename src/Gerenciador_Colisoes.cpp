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

const float Gerenciador_Colisoes::lim_esq = 0.0f;
const float Gerenciador_Colisoes::lim_dir = 1280.0f;
const float Gerenciador_Colisoes::lim_cima = 0.0f;
const float Gerenciador_Colisoes::lim_baixo = 720.0f;

const float Gerenciador_Colisoes::epsilonJanela = 0.5f;
const float Gerenciador_Colisoes::coefRestTeto = 0.15f;

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

    pObs->obstaculizarInim(pInim);
}

void Gerenciador_Colisoes::tratarColisaoChao(Personagem* pP)
{
    if (pP == nullptr || pGround == nullptr)
        return;

    sf::FloatRect pBounds = pP->getBounds();
    sf::FloatRect chaoBounds = pGround->getGlobalBounds();
    sf::FloatRect intersecao;

    if (!pBounds.intersects(chaoBounds, intersecao))
        return;

    const float EPSILON = 0.5f;
    const float COEF_REST_PISO = 0.07f;

    sf::Vector2f vel = pP->getVelocidade();
    sf::Vector2f posAnt = pP->getPosicaoAnterior();

    // Como a origem do personagem está no centro:
    sf::FloatRect boundsAnterior(
        posAnt.x - pBounds.width / 2.0f,
        posAnt.y - pBounds.height / 2.0f,
        pBounds.width,
        pBounds.height
    );

    float anteriorBaixo = boundsAnterior.top + boundsAnterior.height;
    float chaoCima = chaoBounds.top;

    // Só faz sentido o caso do personagem vindo de cima.
    if (anteriorBaixo <= chaoCima)
    {
        pP->setY(pP->getY() - intersecao.height - EPSILON);
        float novaVelY = (-1.0f) * vel.y * COEF_REST_PISO;

        // Evita ficar quicando "ad aeternum" no chão.
        if (novaVelY > -20.0f)
            novaVelY = 0.0f;

        pP->setVelocidadeY(novaVelY);

        float pBottom = pP->getY()+(pBounds.height/2.0f); 
        float chaoTop = pGround->getPosition().y;

        if (abs(pBottom-chaoTop) < 2.0f)
            pP->setNoChao(true);
        else
            pP->setNoChao(false);
        
        /*
        if (novaVelY < 0.0f)
            pP->setNoChao(false);
        else
            pP->setNoChao(true);
        */

        pP->atualizarPosicaoSprite();
    }
}

void Gerenciador_Colisoes::executar()
{
    //estou sempre caindo aqui, portanto aqui chamo todas as verificações necessárias

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

        tratarColisaoChao(pJog);

        caracterOutOfBounds(pJog);

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

            pInim->setNoChao(false);

            if(verificarColisao(pInim, pObs)) 
            {
                tratarColisoesInimObstaculos(pInim, pObs);
                //aplicarGravidade = false;
            }

            tratarColisaoChao(pInim);
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
    if (pe == nullptr) 
        return;

    sf::FloatRect bounds = pe->getBounds();
    Jogador* pJog = dynamic_cast<Jogador*>(pe);
    
    bool corrigiu = false;

    // Saiu pela esquerda
    if (bounds.left < lim_esq)
    {
        pe->setX(lim_esq + (bounds.width/2.0f));
        //pe->setX(pe->getX() + (lim_esq - bounds.left));
        corrigiu = true;
    }

    // Saiu pela direita
    else if (bounds.left + bounds.width > lim_dir)
    {
        pe->setX(lim_dir - (bounds.width/2.0f));
        //pe->setX(pe->getX() - ((bounds.left + bounds.width) - lim_dir));
        corrigiu = true;
    }

    bounds = pe->getBounds();

    // Saiu por cima
    if (bounds.top < lim_cima)
    {
        pe->setY(pe->getY() + (lim_cima - bounds.top));
        corrigiu = true;

        if (pJog != nullptr)
        {
            sf::Vector2f vel = pJog->getVelocidade();

            if (vel.y < 0.0f)
            {
                float novaVelY = (-1.0f) * vel.y * coefRestTeto;

                // Garante um pequeno recuo para baixo.
                if (novaVelY < 60.0f)
                    novaVelY = 60.0f;

                pJog->setVelocidadeY(novaVelY);
                pJog->setNoChao(false);
            }
        }
    }

    // Saiu por baixo
    else if (bounds.top + bounds.height > lim_baixo)
    {
        pe->setY(pe->getY() - ((bounds.top + bounds.height) - lim_baixo));
        corrigiu = true;
    }

    if (corrigiu && pJog != nullptr)
    {
        pJog->atualizarPosicaoSprite();

        sf::Vector2f vel = pJog->getVelocidade();

        if (pJog->getBounds().top <= lim_cima && vel.y < 0.0f)
            pJog->setVelocidadeY(0.0f);

        if (pJog->getBounds().left <= lim_esq && vel.x < 0.0f)
            pJog->setVelocidadeX(0.0f);

        if (pJog->getBounds().left + pJog->getBounds().width >= lim_dir && vel.x > 0.0f)
            pJog->setVelocidadeX(0.0f);
    }
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