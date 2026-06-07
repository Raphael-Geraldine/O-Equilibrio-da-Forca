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
    altura(1),
    directionMov(true)
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

    int chance = rand()%10;

    if (aleatMov.getElapsedTime().asSeconds() >= 2.0f)
    {   
        if (x - (getBounds().width/2.0f) < 10 && chance > 1)
            directionMov = true;
        else if (x + (getBounds().width/2.0f) > 1270 && chance > 1)
            directionMov = false;
        else if ((x>640 && chance > 3)||(x<640 && chance < 4))
            directionMov=false;
        else
            directionMov=true;
        aleatMov.restart();
    }

    if (y + (getBounds().height/2.0f) > 700)
    {
        if (directionMov)
            velocidade.x = 100.0f;
        else
            velocidade.x = -100.0f;
    }

    gravity();
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
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velocidade.x * dt;
    y += velocidade.y * dt;

    atualizarPosicaoSprite();
}
void K_2SO::operator++()
{
    if (num_vidas < 3)
        nivel_maldade+=2;
}

void K_2SO::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    k2Skin.setPosition(x,y);
}
