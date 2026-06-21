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
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;
using namespace Gerenciadores;

#include "SFML/Graphics.hpp"

short int OEquilibrioDaForca::Entidades::Obstaculos::Lava::cont(0);
vector<sf::Vector2i> OEquilibrioDaForca::Entidades::Obstaculos::Lava::lavaPositions;

Lava::Lava(): 
    Obstaculo(), 
    largura(1), 
    danosidade(4),
    nLava(cont++)
{
    lavaPositions.push_back(sf::Vector2i(250, 720));
    lavaPositions.push_back(sf::Vector2i(500, 720));
    lavaPositions.push_back(sf::Vector2i(750, 720));
    lavaPositions.push_back(sf::Vector2i(1180, 720));
    lavaPositions.push_back(sf::Vector2i(950, 720));

    danoso=true;
    emSuperficie = true;
    lavaSkin.setScale(0.20,0.20);

    sf::Texture* pTexturaLava = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(LAVAPNG);
    
    if (pTexturaLava == NULL)
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
    cont=0;
}
void Lava::executar()
{
    aplicarFisica();
    mover();
}
void Lava::salvar()
{
    Obstaculo::salvarDataBuffer();
    if (buffer != NULL)
    {
        *buffer<<cont<<' '<< 'O' <<' '<<"Lava"<<'%';
    }
}
void Lava::obstaculizar (Jogador* pJog)
{
    if (pJog == NULL)
        return;

    sf::FloatRect playerBounds = pJog->getBounds();
    sf::FloatRect lavaBounds = this->getBounds();
    
    bool mergulhado = false;

    //Quando jogador estiver 100% em cima
    if (((pJog->getX() + (playerBounds.width/2.0f)) < (this->getX() + (lavaBounds.width/2.0f))) 
        && 
        ((pJog->getX() - (playerBounds.width/2.0f)) > (this->getX() - (lavaBounds.width/2.0f))))
    {
        pJog->setY(710); //pode exagerar no valor, pois em Colisões não deixa sair da tela
        mergulhado=true;
    }
    else
    {
        pJog->setY(710-(playerBounds.height/1.9f));
        pJog->setEmSuperficie(true);
    }
    
    //danificar
    vector<int>::iterator it;
    vector<sf::Clock>::iterator itClock = clockDano.begin();
    for (it=ids.begin(); it != ids.end(); ++it)
    {
        if(*it == pJog->getID())
        {
            if ((*itClock).getElapsedTime().asSeconds()<0.5f)
            {
                pJog->atualizarPosicaoSprite();
                return;
            }
            
            if (mergulhado)
                danificar(pJog,(int)danosidade);
            else
                danificar(pJog,(int)danosidade/2);
            (*itClock).restart();
            pJog->atualizarPosicaoSprite();
            return;
        }

        ++itClock;
    }

    //Aqui nao achou:
    ids.push_back(pJog->getID());
    if (mergulhado)
        danificar(pJog,(int)danosidade);
    else
        danificar(pJog,(int)danosidade/2);
    sf::Clock clockD;
    clockDano.push_back(clockD);
    pJog->atualizarPosicaoSprite();

    /*
    sf::FloatRect playerBounds = pJog->getBounds();
    sf::FloatRect lavaBounds = this->getBounds();
    
    //Quando jogador estiver 100% em cima
    if (((pJog->getX() + (playerBounds.width/2.0f)) < (this->getX() + (lavaBounds.width/2.0f))) 
        && 
        ((pJog->getX() - (playerBounds.width/2.0f)) > (this->getX() - (lavaBounds.width/2.0f))))
    {
        pJog->setY(710); //pode exagerar no valor, pois em Colisões não deixa sair da tela
        if (clockDano.getElapsedTime().asSeconds()>0.5f)
        {
            danificar(pJog,(int)danosidade);
            clockDano.restart();
        }
        //não tem o pJog->setNoChao(true), para ele não poder pular
    }
    else
    {
        pJog->setY(710-(playerBounds.height/1.9f));
        if (clockDano.getElapsedTime().asSeconds()>0.5f)
        {
            danificar(pJog,(int)danosidade/2);
            clockDano.restart();
        }
        pJog->setNoChao(true);
    }

    pJog->atualizarPosicaoSprite();
    */
}
void Lava::danificar(Jogador* pJog, int dano)
{
    if (pJog == NULL)
        return;

    pJog->sofrerAtaque(dano);
}
void Lava::mover()
{
    y+=velocidade.y * dt;
    lavaSkin.setPosition(x,y);
}
sf::Sprite Lava::getDrawData() const 
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