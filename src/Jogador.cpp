#define ANAKINPNG "../assets/images/Anakin.png"

#include <iostream>
using namespace std;

#include "../include/Personagem.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Jogador.h"

short int TrabalhoJogo::Entidades::Personagens::Jogador::cont(0);

TrabalhoJogo::Entidades::Personagens::Jogador::Jogador(): playerID(cont++)
{
    playerSkin.setScale(0.17,0.17);

    sf::FloatRect bounds = playerSkin.getLocalBounds();
    playerSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    x=20;
    y=570;
    playerSkin.setPosition(x,y);
}

TrabalhoJogo::Entidades::Personagens::Jogador::~Jogador()
{

}
sf::Sprite TrabalhoJogo::Entidades::Personagens::Jogador::getDrawData()
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
    
    return playerSkin;
}
void TrabalhoJogo::Entidades::Personagens::Jogador::executar()
{
    
}
void TrabalhoJogo::Entidades::Personagens::Jogador::salvar()
{
    
}
void TrabalhoJogo::Entidades::Personagens::Jogador::mover()
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

/*void TrabalhoJogo::Entidades::Personagens::Jogador::colidirInimigo(Inimigo* pIn)
{

}
void TrabalhoJogo::Entidades::Personagens::Jogador::colidirObstaculo(Obstaculo* pOb)
{

}*/