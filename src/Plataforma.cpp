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
vector<sf::Vector2i> TrabalhoJogo::Entidades::Obstaculos::Plataforma::platPositions={{270,270},{480,480},{360,360},{540,540},{144,144}};

TrabalhoJogo::Entidades::Obstaculos::Plataforma::Plataforma(float l): 
    Obstaculo(),
    largura(l), 
    platID(cont++)
{
    danoso=false;
    
    platSkin.setScale(0.3,0.3);

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
    return platSkin.getGlobalBounds();
}