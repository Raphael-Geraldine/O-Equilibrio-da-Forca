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

short int Stormtrooper::stromVivos(0);

Stormtrooper::Stormtrooper(): 
    Inimigo(),
    medo(false)
{
    stromVivos++;
    directionMove = true;

    //num_vidas = (rand()%5)+1;
    num_vidas = 5;
    vidaMax = num_vidas;
    nivel_maldade = 4;

    x = (rand()%1100)+100;
    y = 200;

    sf::Texture* pTexturaStormtrooper = pGG->carregarTextura(STORMPNG);

    if (pTexturaStormtrooper == NULL)
    {
        cerr << "Erro de carregamento do PNG do Stormtrooper" << endl;
    }
    else
    {
        skin.setTexture(*pTexturaStormtrooper); 
    }

    sf::FloatRect bounds = skin.getLocalBounds();
    skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    skin.setScale(altura*0.12,altura*0.12);
    atualizarPosicaoSprite();
}

Stormtrooper::Stormtrooper(float sx, float sy, float velx, float vely, int numVidas, int nivelMal): 
    Inimigo(),
    medo(false)
{
    stromVivos++;
    directionMove = true;

    num_vidas = numVidas;
    vidaMax = 5;
    nivel_maldade = nivelMal;

    x = sx;
    y = sy;
    velocidade.x=velx;
    velocidade.y=vely;

    sf::Texture* pTexturaStormtrooper = pGG->carregarTextura(STORMPNG);

    if (pTexturaStormtrooper == NULL)
    {
        cerr << "Erro de carregamento do PNG do Stormtrooper" << endl;
    }
    else
    {
        skin.setTexture(*pTexturaStormtrooper); 
    }

    sf::FloatRect bounds = skin.getLocalBounds();
    skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    skin.setScale(altura*0.12,altura*0.12);
    atualizarPosicaoSprite();
    atualizarBarraVida();
}

Stormtrooper::~Stormtrooper()
{
    stromVivos--;
    num_vidas=-1;
}
void Stormtrooper::executar()
{
    atualizarBarraVida();
    
    salvarPosicaoAnterior();

    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());
    velocidade.x = 0.0f;

    if(stromVivos<3)
        medo=true;

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

    if(medo)
    {
        if (directionMove)
            velocidade.x = 400.0f;
        else
            velocidade.x = -400.0f; 
    }
    else
    {
        if (y + (getBounds().height/2.0f) > 700)
        {
            if (directionMove)
                velocidade.x = 100.0f;
            else
                velocidade.x = -100.0f;  
        }
    }
    
    aplicarFisica();
    mover();
}
void Stormtrooper::salvar()
{
    Inimigo::salvarDataBuffer();

    if (buffer != NULL)
    {
        *buffer << "Stormtrooper" << '%';
    }
}
void Stormtrooper::danificar(Jogador* p)
{
    int chance = rand()%10; 
    if (num_vidas && chance>3)
    {
        if(medo)
            p->sofrerAtaque(nivel_maldade/2);
        else
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
    return skin.getGlobalBounds();
}
sf::Sprite Stormtrooper::getDrawData() const
{   
    return skin;
}

void Stormtrooper::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    skin.setPosition(x,y);
    atualizarPosicaoBarra();
}