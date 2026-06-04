#define LAVAPNG "../assets/images/Lava.png" 

#include <vector>
using namespace std;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Jogador.h"
#include "../include/Lava.h"
#include "../include/Obstaculo.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;
using namespace Gerenciadores;

#include "SFML/Graphics.hpp"

short int TrabalhoJogo::Entidades::Obstaculos::Lava::cont(0);
vector<sf::Vector2i> TrabalhoJogo::Entidades::Obstaculos::Lava::lavaPositions={
    {250, 720}, {500, 720}, {750, 720}, {950, 720}, {1150, 720},
    {300, 720}, {420, 720}, {610, 720}, {850, 720}, {1050, 720}
};

Lava::Lava(): 
    Obstaculo(), 
    largura(1), 
    danosidade(5),
    lavaID(cont++)
{
    danoso=true;

    lavaSkin.setScale(0.25,0.25);

    sf::Texture* pTexturaLava = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(LAVAPNG);
    
    if (pTexturaLava == nullptr)
        cerr << "Erro de carregamento do PNG da Lava" << endl;
        
    else
        lavaSkin.setTexture(*pTexturaLava); 

    sf::FloatRect bounds = lavaSkin.getLocalBounds();
    lavaSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    x=(lavaPositions[lavaID]).x;
    y=(lavaPositions[lavaID]).y;

    lavaSkin.setPosition(x,y);
}
Lava::~Lava()
{

}
void Lava::executar()
{

}
void Lava::salvar()
{

}
void Lava::obstaculizar (Jogador* pJog)
{
    if (pJog == nullptr)
        return;

    executar();
    
    sf::FloatRect playerBounds = pJog->getBounds();
    sf::FloatRect platBounds = this->getBounds();
    
    //......   
}
void Lava::mover()
{
    //não faz nada, mas precisa ter pois a classe pai tem virtual void mover()
}
sf::Sprite Lava::getDrawData()
{
    return lavaSkin;
}
sf::FloatRect Lava::getBounds() const
{
    return lavaSkin.getGlobalBounds();
}