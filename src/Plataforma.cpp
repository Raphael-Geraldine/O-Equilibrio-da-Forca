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

    // Para evitar que o jogador fique exatamente encostado ou
    // levemente sobreposto pós correçao de colisão 
    // (o que se mostrou potencial fonte de bugs).
    const float EPSILON = 0.5f;

    // Coeficiente de restituição (de 0.0f a 1.0f):
    const float COEF_REST_CABECA = 0.10f; 
    const float COEF_REST_PISO = 0.05f;
    const float COEF_REST_LATERAL = 0.05f;
    
    sf::Vector2f vel = pJog->getVelocidade();
    sf::Vector2f posAnt = pJog->getPosicaoAnterior();

    // Tratar quinas, lembrando que sprite está com origem no centro.
    sf::FloatRect boundsAnterior(
        posAnt.x - jogBounds.width / 2.0f,
        posAnt.y - jogBounds.height / 2.0f,
        jogBounds.width,
        jogBounds.height
    );

    float anteriorBaixo = boundsAnterior.top + boundsAnterior.height;
    float anteriorCima = boundsAnterior.top;
    float anteriorDireita = boundsAnterior.left + boundsAnterior.width;
    float anteriorEsquerda = boundsAnterior.left;

    float obsBaixo = obsBounds.top + obsBounds.height;
    float obsCima = obsBounds.top;
    float obsEsquerda = obsBounds.left;
    float obsDireita = obsBounds.left + obsBounds.width;

    // Veio de cima, antes estava acima da plataforma.
    if (anteriorBaixo <= obsCima)
    {
        pJog->setY(pJog->getY() - intersecao.height - EPSILON);
        float novaVelY = (-1.0f) * vel.y * COEF_REST_PISO;

        // Evita ficar quicando "ad aeternum" no chão.
        if (novaVelY > -20.0f)
            novaVelY = 0.0f;

        pJog->setVelocidadeY(novaVelY);
                
        if (novaVelY < 0.0f)
            pJog->setNoChao(false);

        else
            pJog->setNoChao(true);
    }

    // Veio de baixo, antes estava abaixo da plataforma:
    else if (anteriorCima >= obsBaixo)
    {
        pJog->setY(pJog->getY() + intersecao.height + EPSILON);
        float novaVelY = (-1.0f) * vel.y * COEF_REST_CABECA;
        pJog->setVelocidadeY(novaVelY);
        pJog->setNoChao(false);
    }

    // Colisão horizontal:
    else 
    {
        bool colidiuLateral = false;

        // Veio da esquerda:
        if (anteriorDireita <= obsEsquerda)
        {
            pJog->setX(pJog->getX() - intersecao.width - EPSILON);
            colidiuLateral = true;
        }
            

        // Veio da direita:
        else if (anteriorEsquerda >= obsDireita)
        {
            pJog->setX(pJog->getX() + intersecao.width + EPSILON);
            colidiuLateral = true;
        }
            
        if (colidiuLateral) 
        {
            float novaVelX = (-1.0f) * vel.x * COEF_REST_LATERAL;

            // Recuo apenas se tiver impacto suficiente para tal.
            if (novaVelX < 20.0f && novaVelX > -20.0f)
                novaVelX = 0.0f;

            pJog->setVelocidadeX(novaVelX);
        }        
    }

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