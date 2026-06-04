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

    stormSkin.setScale(altura*0.15,altura*0.15);
    stormSkin.setPosition(x,y);
}
Stormtrooper::~Stormtrooper()
{
    num_vidas=-1;
    delete(stormSkin.getTexture());
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
    int chance = rand()%10; 
    if (num_vidas && chance>3)
    {
        p->sofrerAtaque(nivel_maldade/4);
    }
}
void Stormtrooper::mover()
{
    gravity();

    int sort = rand()%10;

    if (aleatMov.getElapsedTime().asSeconds() >= 2.0f)
    {
        if ((x>640 && sort > 3)||(x<640 && sort < 4))
            directionMov=false;
        else
            directionMov=true;

        aleatMov.restart();
    }

    if (directionMov)
        x+=1;
    else
        x-=1;
    
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