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

Stormtrooper::Stormtrooper()
{

}
Stormtrooper::~Stormtrooper()
{

}
void Stormtrooper::executar()
{

}
void Stormtrooper::salvar()
{

}
void Stormtrooper::danificar(Jogador* p)
{

}
void Stormtrooper::mover()
{

}
void Stormtrooper::atirar()
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