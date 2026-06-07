#include "../include/Entidade.h"
#include "../include/Personagem.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include <iostream>
using namespace std;

const float Personagem::pixelsPorMetro = 50.0f;
const float Personagem::gravidadeReal = 9.8f;
const float Personagem::gravidade = gravidadeReal * pixelsPorMetro;
const float Personagem::velocidadeMaxQueda = 900.0f;
const float Personagem::velocidadePulo = -370.0f; //alterei de -420.0f para 370.0f, com "bônus de altura no chão"

Personagem::Personagem(): 
    Entidade(), 
    num_vidas(0),
    velocidade(0.0f, 0.0f),
    noChao(false),
    // 1 segundo / 60 frames = 0,16666... segundos por frame
    dt(1.0f/ 60.0f) 
{

}

Personagem::~Personagem()
{
    
}

/*
void Personagem::atualizarPosicao() 
{
    dt = relogio.getElapsedTime().asSeconds();
    float ds = velFinal.x * dt;
    if (paraEsquerda) {
        ds *= -1;
    }

    corpo.move(ds, 0.0f);
}
*/

void Personagem::salvarDataBuffer()
{
    
}

int Personagem::getVida()
{
    return num_vidas;
}

void Personagem::setDeltaTempo (const float tempo) 
{
    if (tempo > 0.0f) 
    {
        // Parece ser um limite razoável caso o jogo trave,
        // para o jogador não teleportar (no máximo desloca
        // 900 (v_max) * 0,033 px, que corespondem a 1/0.033 
        // = 30 FPS, um atraso de frame de 33 ms). Física 
        // nunca simula frame pior que 30 FPS (tolerância).
        if (tempo > 0.033f)
            dt = 0.033f;
        
        else
            dt = tempo;
    }
}

void Personagem::setVelocidade (const sf::Vector2f vel) 
{
    velocidade = vel;
}

void Personagem::setVelocidadeX (const float vx) 
{
    velocidade.x = vx;
}

void Personagem::setVelocidadeY (const float vy) 
{
    velocidade.y = vy;
}

sf::Vector2f Personagem::getVelocidade () const
{
    return velocidade;
}

void Personagem::setNoChao(const bool emChao)
{
    noChao = emChao;
}

bool Personagem::getNoChao() const 
{
    return noChao;
}

void Personagem::salvarPosicaoAnterior()
{
    posicaoAnterior.x = x;
    posicaoAnterior.y = y;
}

sf::Vector2f Personagem::getPosicaoAnterior() const
{
    return posicaoAnterior;
}

void Personagem::gravity()
{
    if (!noChao)
    {
        // v = v0 + gt;
        // y > 0 para baixo.
        velocidade.y += gravidade * dt;

        if (velocidade.y > velocidadeMaxQueda) 
            velocidade.y = velocidadeMaxQueda;
    }
}

void Personagem::pular() 
{
    bool plataformaFixa = false;

    if (y + (getBounds().height/2.0f) > 705)
        plataformaFixa = true;
    if (noChao) 
    {
        if (plataformaFixa)
        {
            velocidade.y = velocidadePulo-110; // negativo aumenta em y
            noChao = false;
        }
        else
        {
            velocidade.y = velocidadePulo;
            noChao = false;
        }
    }
}