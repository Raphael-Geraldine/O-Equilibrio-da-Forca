#include <string>
using namespace std;

#include "limits.h"
#include"../include/Ente.h"
#include "../include/Entidade.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;

const float Entidade::velocidadeMaxQueda (900.0f);
const float Entidade::pixelsPorMetro (50.0f);
const float Entidade::gravidadeReal (9.8f);
const float Entidade::gravidade (gravidadeReal * pixelsPorMetro);

Entidade::Entidade(): Ente(), buffer(nullptr), x(0), y(0), velocidade(0.0f, 0.0f), dt(1.0f/ 60.0f), derivadoThread(false), semaforoAberto(false),noChao(false)
{}

Entidade::~Entidade()
{
    x = INT_MIN;
    y = INT_MIN;
}

void Entidade::aplicarFisica()
{
    gravitar();
    // Aqui usa o método sem parâmetro, pois o ajuste é manual.
    limitarVelTerminal();
}

void Entidade::gravitar() 
{
    // v = v0 + gt;
    // y > 0 para baixo.
    if (!noChao)
        velocidade.y += gravidade * dt;
}

void Entidade::salvarDataBuffer()
{
    if (buffer != nullptr)
    {
        *buffer<<to_string(x)<<' '<<to_string(y)<<' '<<to_string(velocidade.x)<<' '<<to_string(velocidade.y)<<' ';
    }
}

void Entidade::setBuffer(ostream* arquivo) 
{ 
    buffer = arquivo; 
}

void Entidade::setX(float i) 
{
    x = i;
}

float Entidade::getX() const
{
    return x;
}

void Entidade::setY(float j) 
{
    y = j;
}

float Entidade::getY() const 
{
    return y;
}

void Entidade::setDeltaTempo (const float tempo) 
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

void Entidade::setVelocidade (const sf::Vector2f vel) 
{
    velocidade = vel;
}

void Entidade::setVelocidadeX (const float vx) 
{
    velocidade.x = vx;
}

void Entidade::setVelocidadeY (const float vy) 
{
    velocidade.y = vy;
}

sf::Vector2f Entidade::getVelocidade () const
{
    return velocidade;
}

// Esse será usado para o projétil, que tem
// velocidade terminal propriamente calculada.
void Entidade::limitarVelTerminal(float limiteVel)
{
    // Não aplica para projétil, pois seu limite é -1.0f.
    if (limiteVel <= 0.0f) 
        return;

    if (velocidade.y > limiteVel) 
        velocidade.y = limiteVel;
}

void Entidade::limitarVelTerminal()
{
    if (velocidade.y > velocidadeMaxQueda)
        velocidade.y = velocidadeMaxQueda;
}

const bool Entidade::getDerivadoThread() const
{
    return derivadoThread;
}

bool Entidade::getSemaforo()
{
    return semaforoAberto;
}

void Entidade::setSemaforo(bool b)
{
    semaforoAberto=b;
}

void* Entidade::run()
{
    return NULL;
}

/*
void Entidade::execThreadMutex()
{}
*/