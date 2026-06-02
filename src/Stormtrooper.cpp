#define STORMPNG "../assets/images/Stormtrooper.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Stormtrooper.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

Stormtrooper::Stormtrooper(): Inimigo(), vida(0), altura(1)
{
    vida = (rand()%5)+1;
    x = (rand()%1100)+100;
    y = 680;

    stormSkin.setPosition(x,y);

    if (!stormTexture.loadFromFile(STORMPNG))
    {
        cerr << "Erro de carregamento do PNG do Stormtrooper" << endl;
    }
    else
    {
        stormSkin.setTexture(stormTexture); 
    }

    sf::FloatRect bounds = stormSkin.getLocalBounds();
    stormSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    stormSkin.setScale(0.15,0.15);
}
Stormtrooper::~Stormtrooper()
{
    vida=-1;
}
void Stormtrooper::executar()
{
    mover();
}
void Stormtrooper::salvar()
{

}
void Stormtrooper::danificar(Jogador* p)
{

}
void Stormtrooper::mover()
{
    gravity();

    int direction = rand()%10;

    if (direction > 1)
        x+=2;
    else
        x-=2;
}
void Stormtrooper::atacar()
{

}
sf::FloatRect Stormtrooper::getBounds() const
{
    return stormSkin.getGlobalBounds();
}
sf::Sprite Stormtrooper::getDrawData()
{   
    return stormSkin;
}