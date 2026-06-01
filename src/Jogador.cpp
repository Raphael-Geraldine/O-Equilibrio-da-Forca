#define ANAKINPNG "../assets/images/Anakin.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Jogador.h"

short int Jogador::cont(0);

Jogador::Jogador(): playerID(cont++)
{
    playerSkin.setScale(0.17,0.17);

    x=20;
    y=570;
    playerSkin.setPosition(x,y);
}

Jogador::~Jogador()
{

}
sf::Sprite Jogador::getDrawData()
{
    if (!playerID)
    {
        if (!playerTexture.loadFromFile(ANAKINPNG))
        {
            cerr << "Erro de carregamento do PNG do Jogador 1" << endl;
        }
        else
        {
            playerSkin.setTexture(playerTexture); 
        }
    }
    else
        cout<<"Vai ser ObiWan"<<endl;

    sf::FloatRect bounds = playerSkin.getLocalBounds();
    playerSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    
    return playerSkin;
}
void Jogador::executar()
{
    mover();
    gravity(); // Temporário.
}
void Jogador::salvar()
{
    
}
void Jogador::mover()
{
    //gravity();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        y-=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        y+=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        x+=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        x-=2;

    playerSkin.setPosition(x,y);
}

sf::FloatRect Jogador::getBounds() const
{
    return playerSkin.getGlobalBounds();
}

/*void Jogador::colidirInimigo(Inimigo* pIn)
{

}
void Jogador::colidirObstaculo(Obstaculo* pOb)
{

}*/