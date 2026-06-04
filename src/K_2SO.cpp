#define K2PNG "../assets/images/K-2SO.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/K_2SO.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

K_2SO::K_2SO():
    Inimigo(),
    altura(1)
{
    num_vidas = (rand()%10)+1;
    nivel_maldade = 10;

    x = (rand()%1100)+100;
    y = 200;

    sf::Texture* pTexturaK2 = pGG->carregarTextura(K2PNG);

    if (pTexturaK2 == nullptr)
    {
        cerr << "Erro de carregamento do PNG do K-2SO" << endl;
    }
    else
    {
        k2Skin.setTexture(*pTexturaK2); 
    }

    sf::FloatRect bounds = k2Skin.getLocalBounds();
    k2Skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    k2Skin.setScale(altura*0.15,altura*0.15);
    k2Skin.setPosition(x,y);
}
K_2SO::~K_2SO()
{
    num_vidas=-1;
}
void K_2SO::executar()
{
    mover();
    this->operator++();
}
void K_2SO::danificar(Jogador* p)
{
    int chance = rand()%10; 
    if (num_vidas && chance>3)
    {
        p->sofrerAtaque(nivel_maldade/3);
    }
}
sf::Sprite K_2SO::getDrawData()
{
    return k2Skin;
}
sf::FloatRect K_2SO::getBounds() const
{
    return k2Skin.getGlobalBounds();
}
void K_2SO::salvar()
{

}
void K_2SO::mover()
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
    
    k2Skin.setPosition(x,y);
}
void K_2SO::operator++()
{
    if (num_vidas < 3)
        nivel_maldade+=2;
}