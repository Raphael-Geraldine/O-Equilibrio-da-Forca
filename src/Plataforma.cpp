#define PLATPNG "../assets/images/Plataforma.png"

#include <vector>
using namespace std;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Jogador.h"
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
    {250, 520}, {1030, 520}, {640, 400}, {100, 300}, {1180, 300}, {420, 180}, {860, 180},
    {300, 480}, {980, 480}, {640, 140}, {150, 300}, {1130, 300}, {440, 220}, {840, 220}
};

TrabalhoJogo::Entidades::Obstaculos::Plataforma::Plataforma(float l): 
    Obstaculo(),
    largura(l), 
    platID(cont++)
{
    aplicarGravidade = false;

    danoso=false;
    
    platSkin.setScale(0.2,0.20);

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
                
        if (novaVelY < 0.0f)
            pJog->setNoChao(false);

        else
            pJog->setNoChao(true);

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

void Plataforma::fazEscorregar(Jogador* pJog, const sf::FloatRect& jogBounds, const sf::FloatRect& obsBounds) 
{
    if (pJog == nullptr)
        return;

    float centroJogador = jogBounds.left + jogBounds.width / 2.0f;
    float centroPlataforma = obsBounds.left + obsBounds.width / 2.0f;

    float direcao = 1.0f;

    if (centroJogador < centroPlataforma)
        direcao = -1.0f;

    pJog->setNoChao(false);

    // Empurra o jogador para fora da plataforma.
    pJog->setX(pJog->getX() + direcao * deslocamentoEscorrega);

    // Dá uma velocidade lateral pequena para reforçar a sensação de escorregão.
    pJog->setVelocidadeX(direcao * velocidadeEscorrega);

    pJog->atualizarPosicaoSprite();
}

sf::Sprite TrabalhoJogo::Entidades::Obstaculos::Plataforma::getDrawData()
{   
    return platSkin;
}
sf::FloatRect TrabalhoJogo::Entidades::Obstaculos::Plataforma::getBounds() const
{
    return platSkin.getGlobalBounds();
}