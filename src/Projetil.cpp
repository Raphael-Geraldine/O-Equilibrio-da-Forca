#define PROJETILPNG "../assets/images/Projetil.png"

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
    ativo(true),
    dano(d)
{
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
}
void Projetil::danificar(Jogador* p)
{
}
sf::Sprite Projetil::getDrawData()
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
}
void Projetil::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    projetilSkin.setPosition(x,y);
}

void Projetil::perseguir(Jogador* pJog, AT_ST* pAT)
{

}