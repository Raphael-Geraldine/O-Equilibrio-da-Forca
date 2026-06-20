#define GELOPNG "../assets/images/Gelo.png" 

#include <vector>
using namespace std;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Gelo.h"
#include "../include/Obstaculo.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;
using namespace Gerenciadores;

#include "SFML/Graphics.hpp"

short int OEquilibrioDaForca::Entidades::Obstaculos::Gelo::cont(0);
vector<sf::Vector2i> OEquilibrioDaForca::Entidades::Obstaculos::Gelo::geloPositions={
    {270 /*300*/, 720}, /*{480, 720},*/ {650, 720}, {1080, 720}, {850, 720}
};

Gelo::Gelo(): 
    Obstaculo(), 
    largura(1), 
    danosidade(6),
    nGelo(cont++)
{
    danoso=true;
    emSuperficie = true;
    geloSkin.setScale(0.20,0.20);

    sf::Texture* pTexturaGelo = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(GELOPNG);
    
    if (pTexturaGelo == nullptr)
        cerr << "Erro de carregamento do PNG do Gelo" << endl;
        
    else
        geloSkin.setTexture(*pTexturaGelo); 

    sf::FloatRect bounds = geloSkin.getLocalBounds();
    geloSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    x=(geloPositions[nGelo]).x;
    y=(geloPositions[nGelo]).y;

    geloSkin.setPosition(x,y);
}
Gelo::~Gelo()
{
    cont=0;
}
void Gelo::executar()
{
    gravitar();
    mover();
}
void Gelo::salvar()
{
    Obstaculo::salvarDataBuffer();
    if (buffer != nullptr)
    {
        *buffer<<cont<<' '<< ' '<< 'O' <<' '<< "Gelo" <<'%';
    }
}
void Gelo::obstaculizar (Jogador* pJog)
{
    if (pJog == nullptr)
        return;
    
    sf::FloatRect playerBounds = pJog->getBounds();
    sf::FloatRect GeloBounds = this->getBounds();
    
    //pJog->setY(710-(playerBounds.height/1.9f));
    //pJog->setNoChao(true);
    desacelerar(pJog);

    bool inteiro = false;

    if (((pJog->getX() + (playerBounds.width/2.0f)) < (this->getX() + (GeloBounds.width/2.0f))) 
        && 
        ((pJog->getX() - (playerBounds.width/2.0f)) > (this->getX() - (GeloBounds.width/2.0f))))
        {
            inteiro=true;
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
            
            if (inteiro)
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
    if (inteiro)
        danificar(pJog,(int)danosidade);
    else
        danificar(pJog,(int)danosidade/2);
    sf::Clock clockD;
    clockDano.push_back(clockD);
    pJog->atualizarPosicaoSprite();

    /*
    if (clockDano.getElapsedTime().asSeconds()>0.5f)
    {
        //Quando jogador estiver 100% em cima
        if (((pJog->getX() + (playerBounds.width/2.0f)) < (this->getX() + (GeloBounds.width/2.0f))) 
            && 
            ((pJog->getX() - (playerBounds.width/2.0f)) > (this->getX() - (GeloBounds.width/2.0f))))
        {
            danificar(pJog,(int)danosidade);
        }
        else
            danificar(pJog,(int)danosidade/2);
    
        clockDano.restart();
    }

    pJog->atualizarPosicaoSprite();
    */
}
void Gelo::danificar(Jogador* pJog, int dano)
{
    if (pJog == nullptr)
        return;

    pJog->sofrerAtaque(dano);
}
void Gelo::desacelerar(Jogador* pJog)
{
    sf::Vector2f velocidadeJog = pJog->getVelocidade();
    float velx = (velocidadeJog.x + (velocidadeJog.x)*(-1)*(0.25f))*(-1);
    float vely = (velocidadeJog.y + (velocidadeJog.y)*(-1)*(0.25f))*(-1);
    pJog->deslocar(velx,vely);
}
void Gelo::mover()
{
    y+=velocidade.y * dt;
    geloSkin.setPosition(x,y);
}
sf::Sprite Gelo::getDrawData() const 
{
    return geloSkin;
}
sf::FloatRect Gelo::getBounds() const
{
    return geloSkin.getGlobalBounds();
}

void Gelo::obstaculizarInim(Inimigo* pInim)
{
    
}