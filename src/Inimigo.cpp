#define VIDA100PNG "../assets/images/Vida100.png"
#define VIDA75PNG "../assets/images/Vida75.png"
#define VIDA50PNG "../assets/images/Vida50.png"
#define VIDA25PNG "../assets/images/Vida25.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;
using namespace Entidades;
using namespace Personagens;

Inimigo::Inimigo(): 
    Personagem(),
    coolDownAtaque(0.0f),
    directionMove(false),
    nivel_maldade(1),
    vidaMax(0)
{
    pVida100 = pGG->carregarTextura(VIDA100PNG);
    pVida75 = pGG->carregarTextura(VIDA75PNG);
    pVida50 = pGG->carregarTextura(VIDA50PNG);
    pVida25 = pGG->carregarTextura(VIDA25PNG);

    if (pVida100 == NULL || pVida75 == NULL || pVida50 == NULL || pVida25 == NULL)
    {
        cerr << "Erro de carregamento da barra de vida dos Inimigos" << endl;
    }
    else
    {
        barraVida.setTexture(*pVida100); 
    }

    sf::FloatRect bounds = barraVida.getLocalBounds();
    barraVida.setOrigin(bounds.left, bounds.top + bounds.height);

    barraVida.setScale(0.1,0.1);
}

Inimigo::~Inimigo()
{
    nivel_maldade = -1;
    vidaMax = -1;
}
void Inimigo::salvarDataBuffer()
{
    Personagem::salvarDataBuffer();
    
    if (buffer != NULL)
    {
        *buffer << nivel_maldade << ' ';
        // *buffer << to_string(nivel_maldade) << ' ';
    }
}

void Inimigo::tentarDanificar(Jogador* pJ)
{
    if (clockAtaque.getElapsedTime().asSeconds() >= cooldownAtaque)
    {
        danificar(pJ);
        clockAtaque.restart();
    }
}

void Inimigo::danificar(Jogador* pJ)
{
    pJ->sofrerAtaque(nivel_maldade/2);
}                  

void Inimigo::sofrerAtaque(int dano)
{
    num_vidas-=dano;
}

void Inimigo::atualizarBarraVida()
{
    //cout<<getID()<<": "<<(float)num_vidas<<endl;
    //cout<<getID()<<": "<<(float)vidaMax<<endl;
    float vidaAtual = ((float)num_vidas)/((float)vidaMax);
    //cout<<getID()<<": "<<vidaAtual<<endl;
    if(vidaAtual <= 0.25f)
        barraVida.setTexture(*pVida25);
    else if(vidaAtual <= 0.5f)
        barraVida.setTexture(*pVida50);
    else if(vidaAtual <= 0.75f)
        barraVida.setTexture(*pVida75);
}

void Inimigo::atualizarPosicaoBarra() 
{	
    barraVida.setPosition(getBounds().left, getBounds().top);
}

sf::Sprite Inimigo::getBarraVida() const
{   
    return barraVida;
}