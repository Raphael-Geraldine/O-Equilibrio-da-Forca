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
    
    platSkin.setScale(0.25,0.25);

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

    // bool intersects (const Rect< T > &rectangle, Rect< T > &intersection) const
    // Método sobrecarregado retorna o retângulo sobreposto no parâmetro de intersecao
    // Método público sobrecarregado de sf::Rect<T>
    if (!jogBounds.intersects(obsBounds, intersecao))
        return;

    cout << "COLIDIU COM PLATAFORMA | "
     << "intersecao.w=" << intersecao.width
     << " intersecao.h=" << intersecao.height
     << " velY=" << pJog->getVelocidade().y
     << endl;

    // Colisão vertical:
    if (intersecao.height < intersecao.width)
    {
        // Jogador acima do obstáculo:
        if (jogBounds.top < obsBounds.top)
        {
            pJog->setY(pJog->getY() - intersecao.height);
            pJog->setVelocidadeY(0.0f);
            pJog->setNoChao(true);
        }

        // Jogador bate a cabeça no obstáculo:
        else
        {
            pJog->setY(pJog->getY() + intersecao.height);
            pJog->setVelocidadeY(0.0f);
        }
    }

    // Colisão horizontal:
    else
    {
        // Jogador à esquerda do obstáculo:
        if (jogBounds.left < obsBounds.left)
        {
            pJog->setX(pJog->getX() - intersecao.width);
            pJog->setVelocidadeX(0.0f);
        }

        // Jogador à direita do obstáculo:
        else 
        {
            pJog->setX(pJog->getX() + intersecao.width);
            pJog->setVelocidadeX(0.0f);
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