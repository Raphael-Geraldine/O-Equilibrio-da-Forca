#define PROJETILPNG "../assets/images/Laser.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Projetil.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/AT_ST.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

Projetil::Projetil(short int d):
    Entidade(),
    ativo(false),
    dano(d)
{
    x=1700;
    y=800;

    sf::Texture* pTexturaP = pGG->carregarTextura(PROJETILPNG);

    if (pTexturaP == nullptr)
    {
        cerr << "Erro de carregamento do PNG do Projetil" << endl;
    }
    else
    {
        projetilSkin.setTexture(*pTexturaP); 
    }

    sf::FloatRect bounds = projetilSkin.getLocalBounds();
    projetilSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    projetilSkin.setScale(0.15,0.15);

    atualizarPosicaoSprite();
}
Projetil::~Projetil()
{
    ativo=false;
}
void Projetil::executar()
{
    if (ativo)
        mover();
}
void Projetil::danificar(Jogador* p)
{
    if (ativo)
    {
        p->sofrerAtaque(dano);
        ativo=false;
        x=1700;
        y=800;
        atualizarPosicaoSprite();
    }
}
sf::Sprite Projetil::getDrawData() const 
{
    return projetilSkin;
}
sf::FloatRect Projetil::getBounds() const
{
    return projetilSkin.getGlobalBounds();
}
void Projetil::salvar()
{

}
void Projetil::mover()
{
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velocidade.x * dt;
    y += velocidade.y * dt;

    if((x+(getBounds().width/2.0f))<0 || (x-(getBounds().width/2.0f))>1280 
        || (y+(getBounds().height/2.0f))<0 || (y-(getBounds().height/2.0f))>720)
    {
        ativo=false;
        x=1700;
        y=800;
    }

    atualizarPosicaoSprite();
}
void Projetil::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    projetilSkin.setPosition(x,y);
}

void Projetil::perseguir(Jogador* pJog, AT_ST* pAT)
{
    ativo = true;

    sf::Vector2f posJog = pJog->getPosicaoAnterior();
    sf::Vector2f posAT = pAT->getPosicaoAnterior();

    x=posAT.x;
    y=posAT.y;

    //projetilSkin.setRotation(/*ângulo*/);
    atualizarPosicaoSprite();

    float vx = (posJog.x - x)/5;
    float vy = (posJog.y - y)/5;
    setVelocidadeX(vx);
    setVelocidadeY(vy);
}

bool Projetil::getAtivo() const
{
    return ativo;
}