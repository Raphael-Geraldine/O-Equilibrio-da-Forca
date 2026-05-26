#define PLATPNG "../assets/images/Plataforma.png"

#include <vector>
#include <iostream>
using namespace std;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Plataforma.h"

short int TrabalhoJogo::Entidades::Obstaculos::Plataforma::cont(0);
vector<sf::Vector2i> TrabalhoJogo::Entidades::Obstaculos::Plataforma::platPositions={{270,270},{480,480},{360,360},{540,540},{144,144}};

TrabalhoJogo::Entidades::Obstaculos::Plataforma::Plataforma(float l): largura(l), platID(cont++)
{
    danoso=false;

    platSkin.setScale(0.3,0.3);
    
    if (!platTexture.loadFromFile(PLATPNG))
    {
        cerr << "Erro de carregamento do PNG da Plataforms" << endl;
    }
    else
    {
        platSkin.setTexture(platTexture); 
    }

    x=(platPositions[platID]).x;
    y=(platPositions[platID]).y;

    platSkin.setPosition(x,y);

    cout<<x<<endl;
    cout<<y<<endl;
}
TrabalhoJogo::Entidades::Obstaculos::Plataforma::~Plataforma()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::executar()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::salvar()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::mover()
{}
void TrabalhoJogo::Entidades::Obstaculos::Plataforma::obstaculizar(Jogador* p)
{}
sf::Sprite TrabalhoJogo::Entidades::Obstaculos::Plataforma::getDrawData()
{   
    return platSkin;
}
sf::FloatRect TrabalhoJogo::Entidades::Obstaculos::Plataforma::getBounds() const
{
    return sf::FloatRect(x, y, 11.0f, 6.0f);
}