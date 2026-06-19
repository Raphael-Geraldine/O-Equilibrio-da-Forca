#define STORMPNG "../assets/images/Stormtrooper.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using namespace std;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Stormtrooper.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

Stormtrooper::Stormtrooper(): 
    Inimigo(),
    altura(1),
    directionMove(true)
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

    stormSkin.setScale(altura*0.12,altura*0.12);
    atualizarPosicaoSprite();
}

Stormtrooper::Stormtrooper(float sx, float sy, float velx, float vely, int numVidas, int nivelMal): 
    Inimigo(),
    altura(1),
    directionMove(true)
{
    num_vidas = numVidas;
    nivel_maldade = nivelMal;

    x = sx;
    y = sy;
    velocidade.x=velx;
    velocidade.y=vely;

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

    stormSkin.setScale(altura*0.12,altura*0.12);
    atualizarPosicaoSprite();
}

Stormtrooper::~Stormtrooper()
{
    num_vidas=-1;
}
void Stormtrooper::executar()
{
    salvarPosicaoAnterior();

    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());
    velocidade.x = 0.0f;

    int chance = rand()%10;

    if (aleatMov.getElapsedTime().asSeconds() >= 2.0f)
    {
        if (x - (getBounds().width/2.0f) < 10 && chance > 1)
            directionMove = true;
        else if (x + (getBounds().width/2.0f) > 1270 && chance > 1)
            directionMove = false;
        else if ((x>640 && chance > 3)||(x<640 && chance < 4))
            directionMove=false;
        else
            directionMove=true;

        aleatMov.restart();
    }

    if (y + (getBounds().height/2.0f) > 700)
    {
        if (directionMove)
            velocidade.x = 100.0f;
        else
            velocidade.x = -100.0f;   
    }
    
    aplicarFisica();
    mover();
}
void Stormtrooper::salvar()
{
    Inimigo::salvarDataBuffer();

    if (buffer != nullptr)
    {
        *buffer << "Stormtrooper" << '%';
    }
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
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velocidade.x * dt;
    y += velocidade.y * dt;

    atualizarPosicaoSprite();
}
sf::FloatRect Stormtrooper::getBounds() const
{
    return stormSkin.getGlobalBounds();
}
sf::Sprite Stormtrooper::getDrawData() const
{   
    return stormSkin;
}

void Stormtrooper::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    stormSkin.setPosition(x,y);
}