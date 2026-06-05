#define PLATPNG "../assets/images/Plataforma.png"

#include <vector>
#include <stdlib.h>
using namespace std;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Plataforma.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;
using namespace Gerenciadores;

const float Plataforma::epsilonColisao = 0.5f;
const float Plataforma::coefRestCabeca = 0.10f;
const float Plataforma::coefRestPiso = 0.05f;
const float Plataforma::coefRestLateral = 0.05f;
const float Plataforma::apoioMinimo = 0.5f;
const float Plataforma::deslocamentoEscorrega = 2.0f;
const float Plataforma::velocidadeEscorrega = 80.0f;

short int TrabalhoJogo::Entidades::Obstaculos::Plataforma::cont(0);
vector<sf::Vector2i> TrabalhoJogo::Entidades::Obstaculos::Plataforma::platPositions={
    {250, 520}, {1030, 520}, {640, 400}, {100, 280}, {1180, 280}, {860, 320},
    {300, 480}, {980, 480}, {640, 140}, {150, 300}, {1130, 300}, {440, 220}
};

TrabalhoJogo::Entidades::Obstaculos::Plataforma::Plataforma(float l): 
    Obstaculo(),
    largura(l), 
    platID(cont++)
{
    aplicarGravidade = false;

    danoso=false;
    
    platSkin.setScale(0.15,0.15);

    sf::Texture* pTexturaPlataforma = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(PLATPNG);
    
    if (pTexturaPlataforma == nullptr)
        cerr << "Erro de carregamento do PNG da Plataforms" << endl;
        
    else
        platSkin.setTexture(*pTexturaPlataforma); 

    sf::FloatRect bounds = platSkin.getLocalBounds();
    platSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    x=(platPositions[platID]).x;
    y=(platPositions[platID]).y;

    platSkin.setPosition(x,y);
}
Plataforma::~Plataforma()
{
    // TIRAR SEG FAULT: delete(platSkin.getTexture());
}
void Plataforma::executar()
{}
void Plataforma::salvar()
{}
void Plataforma::mover()
{}

void Plataforma::obstaculizar(Jogador* pJog)
{
    if (pJog == nullptr) 
        return;    

    sf::FloatRect jogBounds = pJog->getBounds();
    sf::FloatRect obsBounds = this->getBounds();
    sf::FloatRect intersecao;

    if (!jogBounds.intersects(obsBounds, intersecao))
        return;
    
    sf::Vector2f vel = pJog->getVelocidade();
    sf::Vector2f posAnt = pJog->getPosicaoAnterior();

    // Tratar quinas, lembrando que sprite está com origem no centro.
    sf::FloatRect boundsAnterior(posAnt.x - jogBounds.width / 2.0f,
    posAnt.y - jogBounds.height / 2.0f, jogBounds.width, jogBounds.height);

    float anteriorBaixo = boundsAnterior.top + boundsAnterior.height;
    float anteriorCima = boundsAnterior.top;
    float anteriorDireita = boundsAnterior.left + boundsAnterior.width;
    float anteriorEsquerda = boundsAnterior.left;

    float obsBaixo = obsBounds.top + obsBounds.height;
    float obsCima = obsBounds.top;
    float obsEsquerda = obsBounds.left;
    float obsDireita = obsBounds.left + obsBounds.width;

    bool colisaoResolvida = false;
    bool colidiuLateral = false;

    // Veio de cima, antes estava acima da plataforma.
    if (anteriorBaixo <= obsCima)
    {
        float porcentagemApoio = intersecao.width / jogBounds.width;

        if (porcentagemApoio < apoioMinimo)
        {
            fazEscorregar(pJog, jogBounds, obsBounds);
            return;
        }

        pJog->setY(pJog->getY() - intersecao.height - epsilonColisao);
        float novaVelY = (-1.0f) * vel.y * coefRestPiso;

        // Evita ficar quicando "ad aeternum" no chão.
        if (novaVelY > -20.0f)
            novaVelY = 0.0f;

        pJog->setVelocidadeY(novaVelY);
            
        float jogBottom = pJog->getY()+(jogBounds.height/2.0f); 
        float platTop = this->getY()-(obsBounds.height/2.0f);

        if (abs(jogBottom-platTop) < 2.0f)
            pJog->setNoChao(true);
        else
            pJog->setNoChao(false);

        /*
        if (novaVelY < 0.0f)
            pJog->setNoChao(false);

        else
            pJog->setNoChao(true);
        */

        colisaoResolvida = true;
    }

    // Veio de baixo, antes estava abaixo da plataforma:
    else if (anteriorCima >= obsBaixo)
    {
        pJog->setY(pJog->getY() + intersecao.height + epsilonColisao);
        float novaVelY = (-1.0f) * vel.y * coefRestPiso;
        pJog->setVelocidadeY(novaVelY);
        colisaoResolvida = true;
    }

    // Veio da esquerda:
    else if (anteriorDireita <= obsEsquerda)
    {
        pJog->setX(pJog->getX() - intersecao.width - epsilonColisao);
        colidiuLateral = true; 
    }
 
    // Veio da direita:
    else if (anteriorEsquerda >= obsDireita)
    {
        pJog->setX(pJog->getX() + intersecao.width + epsilonColisao);
        colidiuLateral = true;  
    }
            
    if (colidiuLateral) 
    {    
        float novaVelX = (-1.0f) * vel.x * coefRestLateral;  

        // Recuo apenas se tiver impacto suficiente para tal.
        if (novaVelX < 20.0f && novaVelX > -20.0f)
            novaVelX = 0.0f;

        pJog->setVelocidadeX(novaVelX);
        colisaoResolvida = true;
    }        

    // Para colisões usando W + A (diagonal), a posição anterior e final 
    // não resolvia (atravessava o objeto).
    if (!colisaoResolvida)
    {
        if (intersecao.height < intersecao.width)
        {
            if (vel.y < 0.0f)
            {
                pJog->setY(pJog->getY() + intersecao.height + epsilonColisao);
                pJog->setVelocidadeY(0.0f);
                pJog->setNoChao(false);
            }
            else
            {
                pJog->setY(pJog->getY() - intersecao.height - epsilonColisao);
                pJog->setVelocidadeY(0.0f);
                pJog->setNoChao(true);
            }
        }
        else
        {
            if (vel.x < 0.0f)
                pJog->setX(pJog->getX() + intersecao.width + epsilonColisao);
            else
                pJog->setX(pJog->getX() - intersecao.width - epsilonColisao);

            pJog->setVelocidadeX(0.0f);
        }
    }

    pJog->atualizarPosicaoSprite();  
}

void Plataforma::fazEscorregar(Personagem* pP, const sf::FloatRect& pBounds, const sf::FloatRect& obsBounds) 
{
    if (pP == nullptr)
        return;

    float centroPersonagem = pBounds.left + pBounds.width / 2.0f;
    float centroPlataforma = obsBounds.left + obsBounds.width / 2.0f;

    float direcao = 1.0f;

    if (centroPersonagem < centroPlataforma)
        direcao = -1.0f;

    pP->setNoChao(false);

    // Empurra o personagem para fora da plataforma.
    pP->setX(pP->getX() + direcao * deslocamentoEscorrega);

    // Dá uma velocidade lateral pequena para reforçar a sensação de escorregão.
    pP->setVelocidadeX(direcao * velocidadeEscorrega);

    pP->atualizarPosicaoSprite();
}

sf::Sprite Plataforma::getDrawData()
{   
    return platSkin;
}
sf::FloatRect Plataforma::getBounds() const
{
    return platSkin.getGlobalBounds();
}

void Plataforma::obstaculizarInim(Inimigo* pInim)
{
    if (pInim == nullptr) 
        return;    

    sf::FloatRect inimBounds = pInim->getBounds();
    sf::FloatRect obsBounds = this->getBounds();
    sf::FloatRect intersecao;

    if (!inimBounds.intersects(obsBounds, intersecao))
        return;
    
    sf::Vector2f vel = pInim->getVelocidade();
    sf::Vector2f posAnt = pInim->getPosicaoAnterior();

    // Tratar quinas, lembrando que sprite está com origem no centro.
    sf::FloatRect boundsAnterior(posAnt.x - inimBounds.width / 2.0f,
    posAnt.y - inimBounds.height / 2.0f, inimBounds.width, inimBounds.height);

    float anteriorBaixo = boundsAnterior.top + boundsAnterior.height;
    float anteriorCima = boundsAnterior.top;
    float anteriorDireita = boundsAnterior.left + boundsAnterior.width;
    float anteriorEsquerda = boundsAnterior.left;

    float obsBaixo = obsBounds.top + obsBounds.height;
    float obsCima = obsBounds.top;
    float obsEsquerda = obsBounds.left;
    float obsDireita = obsBounds.left + obsBounds.width;

    bool colisaoResolvida = false;
    bool colidiuLateral = false;

    // Veio de cima, antes estava acima da plataforma.
    if (anteriorBaixo <= obsCima)
    {
        float porcentagemApoio = intersecao.width / inimBounds.width;

        if (porcentagemApoio < apoioMinimo)
        {
            fazEscorregar(pInim, inimBounds, obsBounds);
            return;
        }

        pInim->setY(pInim->getY() - intersecao.height - epsilonColisao);
        float novaVelY = (-1.0f) * vel.y * coefRestPiso;

        // Evita ficar quicando "ad aeternum" no chão.
        if (novaVelY > -20.0f)
            novaVelY = 0.0f;

        pInim->setVelocidadeY(novaVelY);
            
        float inimBottom = pInim->getY()+(inimBounds.height/2.0f); 
        float platTop = this->getY()-(obsBounds.height/2.0f);

        if (abs(inimBottom-platTop) < 2.0f)
            pInim->setNoChao(true);
        else
            pInim->setNoChao(false);

        /*
        if (novaVelY < 0.0f)
            pJog->setNoChao(false);

        else
            pJog->setNoChao(true);
        */

        colisaoResolvida = true;
    }

    // Veio de baixo, antes estava abaixo da plataforma:
    else if (anteriorCima >= obsBaixo)
    {
        pInim->setY(pInim->getY() + intersecao.height + epsilonColisao);
        float novaVelY = (-1.0f) * vel.y * coefRestPiso;
        pInim->setVelocidadeY(novaVelY);
        colisaoResolvida = true;
    }

    // Veio da esquerda:
    else if (anteriorDireita <= obsEsquerda)
    {
        pInim->setX(pInim->getX() - intersecao.width - epsilonColisao);
        colidiuLateral = true; 
    }
 
    // Veio da direita:
    else if (anteriorEsquerda >= obsDireita)
    {
        pInim->setX(pInim->getX() + intersecao.width + epsilonColisao);
        colidiuLateral = true;  
    }
            
    if (colidiuLateral) 
    {    
        float novaVelX = (-1.0f) * vel.x * coefRestLateral;  

        // Recuo apenas se tiver impacto suficiente para tal.
        if (novaVelX < 20.0f && novaVelX > -20.0f)
            novaVelX = 0.0f;

        pInim->setVelocidadeX(novaVelX);
        colisaoResolvida = true;
    }        

    // Para colisões usando W + A (diagonal), a posição anterior e final 
    // não resolvia (atravessava o objeto).
    if (!colisaoResolvida)
    {
        if (intersecao.height < intersecao.width)
        {
            if (vel.y < 0.0f)
            {
                pInim->setY(pInim->getY() + intersecao.height + epsilonColisao);
                pInim->setVelocidadeY(0.0f);
                pInim->setNoChao(false);
            }
            else
            {
                pInim->setY(pInim->getY() - intersecao.height - epsilonColisao);
                pInim->setVelocidadeY(0.0f);
                pInim->setNoChao(true);
            }
        }
        else
        {
            if (vel.x < 0.0f)
                pInim->setX(pInim->getX() + intersecao.width + epsilonColisao);
            else
                pInim->setX(pInim->getX() - intersecao.width - epsilonColisao);

            pInim->setVelocidadeX(0.0f);
        }
    }

    pInim->atualizarPosicaoSprite();  
}

/*
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
*/