#define LAVAPNG "../assets/images/Lava.png" 

#include <vector>
using namespace std;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Jogador.h"
#include "../include/Inimigo.h"
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
    {250, 720}, {500, 720}, {750, 720}, {1180, 720}, {950, 720}
};

Lava::Lava(): 
    Obstaculo(), 
    largura(1), 
    danosidade(5),
    nLava(cont++)
{
    danoso=true;
    noChao = true;
    lavaSkin.setScale(0.20,0.20);

    sf::Texture* pTexturaLava = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(LAVAPNG);
    
    if (pTexturaLava == nullptr)
        cerr << "Erro de carregamento do PNG da Lava" << endl;
        
    else
        lavaSkin.setTexture(*pTexturaLava); 

    sf::FloatRect bounds = lavaSkin.getLocalBounds();
    lavaSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    x=(lavaPositions[nLava]).x;
    y=(lavaPositions[nLava]).y;

    lavaSkin.setPosition(x,y);
}
Lava::~Lava()
{

}
void Lava::executar()
{
    gravity();
    mover();
}
void Lava::salvar()
{

}
void Lava::obstaculizar (Jogador* pJog)
{
    if (pJog == nullptr)
        return;
    
    sf::FloatRect playerBounds = pJog->getBounds();
    sf::FloatRect lavaBounds = this->getBounds();
    
    //Quando jogador estiver 100% em cima
    if (((pJog->getX() + (playerBounds.width/2.0f)) < (this->getX() + (lavaBounds.width/2.0f))) 
        && 
        ((pJog->getX() - (playerBounds.width/2.0f)) > (this->getX() - (lavaBounds.width/2.0f))))
    {
        pJog->setY(710); //pode exagerar no valor, pois em Colisões não deixa sair da tela
        danificar(pJog,(int)danosidade);
        //não tem o pJog->setNoChao(true), para ele não poder pular
    }
    else
    {
        pJog->setY(710-(playerBounds.height/1.9f));
        danificar(pJog,(int)danosidade/2);
        pJog->setNoChao(true);
    }
  
    pJog->atualizarPosicaoSprite();
}
void Lava::danificar(Jogador* pJog, int dano)
{
    if (pJog == nullptr)
        return;

    pJog->sofrerAtaque(dano);
}
void Lava::mover()
{
    y+=velocidade.y * dt;
    lavaSkin.setPosition(x,y);
}
sf::Sprite Lava::getDrawData()
{
    return lavaSkin;
}
sf::FloatRect Lava::getBounds() const
{
    return lavaSkin.getGlobalBounds();
}

void Lava::obstaculizarInim(Inimigo* pInim)
{
    
}