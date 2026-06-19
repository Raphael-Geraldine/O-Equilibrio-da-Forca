#define K2PNG "../assets/images/K-2SO.png"
#define K2DANOPNG "../assets/images/K-2SODamage.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using namespace std;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/K_2SO.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

// Construtora sem saving:
K_2SO::K_2SO():
    Inimigo(),
    altura(1),
    cooldownSalto(3.0f),
    impulsaoSalto(520.0f)
{
    directionMove = true;

    num_vidas = (rand() % 5) + 6; // 5 a 10 vidas
    nivel_maldade = 10;

    x = (rand() % 1101) + 100; // x: 100 a 1100 
    y = 200; 

    pTexturaK2 = pGG->carregarTextura(K2PNG);
    pTexturaDanoK2 = pGG->carregarTextura(K2DANOPNG);

    if (pTexturaK2 == nullptr || pTexturaDanoK2 == nullptr)
        cerr << "Erro de carregamento do PNG do K-2SO" << endl;
    else
        k2Skin.setTexture(*pTexturaK2); 

    sf::FloatRect bounds = k2Skin.getLocalBounds();
    k2Skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    k2Skin.setScale(altura*0.15f, altura*0.15f); // Adiconado "f" - float
    atualizarPosicaoSprite();
}

K_2SO::K_2SO(float sx, float sy, float velx, float vely, int numVidas, int nivelMal):
    Inimigo(),
    altura(1),
    cooldownSalto(3.0f),
    impulsaoSalto(520.0f)
{
    directionMove = true;

    num_vidas = numVidas;
    nivel_maldade = nivelMal;

    x = sx;
    y = sy;

    velocidade.x=velx;
    velocidade.y=vely;

    pTexturaK2 = pGG->carregarTextura(K2PNG);
    pTexturaDanoK2 = pGG->carregarTextura(K2DANOPNG);

    if (pTexturaK2 == nullptr || pTexturaDanoK2 == nullptr)
        cerr << "Erro de carregamento do PNG do K-2SO" << endl;

    else
        k2Skin.setTexture(*pTexturaK2); 

    sf::FloatRect bounds = k2Skin.getLocalBounds();
    k2Skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    k2Skin.setScale(altura*0.15f, altura*0.15f);
    atualizarPosicaoSprite();
}

K_2SO::~K_2SO()
{
    num_vidas=-1;
}
void K_2SO::executar()
{
    salvarPosicaoAnterior();
    
    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());
    velocidade.x = 0.0f;

    if ((k2Skin.getTexture() == pTexturaDanoK2) && (textureClock.getElapsedTime().asMilliseconds() >= 150))
        k2Skin.setTexture(*pTexturaK2);

    int chance = rand() % 10;

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

        this->operator++();
    }

    // VER SE NÃO DÁ PARA USAR DE PERSONAGEM
    if (y + (getBounds().height/2.0f) > 700)
    {
        if (directionMove)
            velocidade.x = 100.0f;
            
        else
            velocidade.x = -100.0f;
    }

    tentarPular();
    aplicarFisica();
    mover();
}
void K_2SO::danificar(Jogador* p)
{
    int chance = rand()%10; 
    if (num_vidas && chance>3)
    {
        p->sofrerAtaque(nivel_maldade/3);
    }
}
sf::Sprite K_2SO::getDrawData() const
{
    return k2Skin;
}
sf::FloatRect K_2SO::getBounds() const
{
    return k2Skin.getGlobalBounds();
}
void K_2SO::salvar()
{
    Inimigo::salvarDataBuffer();

    if (buffer != nullptr)
    {
        *buffer << "K_2SO" << '%';
    }
}
void K_2SO::mover()
{
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velocidade.x * dt;
    y += velocidade.y * dt;

    atualizarPosicaoSprite();
}
void K_2SO::operator++()
{
    if (num_vidas < 3 && nivel_maldade < 20)
        nivel_maldade+=2;
}

void K_2SO::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    k2Skin.setPosition(x,y);
}

void K_2SO::sofrerAtaque(int dano)
{
    num_vidas-=dano;
    k2Skin.setTexture(*pTexturaDanoK2); 
    textureClock.restart();
}

void K_2SO::tentarPular()
{
    if (!getNoChao())
        return;

    if (clockSalto.getElapsedTime().asSeconds() < cooldownSalto)
        return;

    velocidade.y = - impulsaoSalto;
    clockSalto.restart();
}