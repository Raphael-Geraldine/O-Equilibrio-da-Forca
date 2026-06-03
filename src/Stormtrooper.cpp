#define STORMPNG "../assets/images/Stormtrooper.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Stormtrooper.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

Stormtrooper::Stormtrooper(): 
    Inimigo(),
    altura(1)
{
    num_vidas = (rand()%5)+1;
    nivel_maldade = 4;

    x = (rand()%1100)+100;
    y = 200;

     sf::Texture* pTexturaStormtrooper = pGG->carregarTextura(STORMPNG);

    if (pTexturaStormtrooper == nullptr)
    {
        cerr << "Erro de carregamento do PNG do Stormtrooper" << endl;
    }
    else
    {
        stormSkin.setTexture(*pTexturaStormtrooper); 
    }

    sf::FloatRect bounds = stormSkin.getLocalBounds();
    stormSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    stormSkin.setScale(0.15,0.15);
    stormSkin.setPosition(x,y);
}
Stormtrooper::~Stormtrooper()
{
    num_vidas=-1;
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
    int chance = rand()%1000; 
    if (num_vidas && chance>987)
    {
        p->sofrerAtaque(nivel_maldade/4);
    }
}
void Stormtrooper::mover()
{
    gravity();

    int direction = rand()%10;

    if (direction > 3)
        x-=2;
    else
        x+=2;

    stormSkin.setPosition(x,y);
}
sf::FloatRect Stormtrooper::getBounds() const
{
    return stormSkin.getGlobalBounds();
}
sf::Sprite Stormtrooper::getDrawData()
{   
    return stormSkin;
}