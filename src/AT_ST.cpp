#define ATPNG "../assets/images/AT_ST.png"
#define ATDANOPNG "../assets/images/AT_STDamage.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cmath>
using std::sqrt;

#include <string>
using namespace std;

#include "../include/Projetil.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/AT_ST.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>
#include <stdlib.h>

AT_ST::AT_ST():
    Inimigo(),
    Thread(),
    altura(1),
    directionMove(true),
    pProj(NULL),
    alvo1(NULL),
    alvo2(NULL)
{
    derivadoThread=true;
    
    //num_vidas = (rand()%10)+10;
    num_vidas = 20;
    vidaMax = num_vidas;
    nivel_maldade = 15;

    x = (rand()%1100)+100;
    y = 600;

    pTexturaAT = pGG->carregarTextura(ATPNG);
    pTexturaDanoAT = pGG->carregarTextura(ATDANOPNG);

    if (pTexturaAT == NULL || pTexturaDanoAT == NULL)
        cerr << "Erro de carregamento do PNG do AT-ST" << endl;
    else
        atSkin.setTexture(*pTexturaAT); 

    sf::FloatRect bounds = atSkin.getLocalBounds();
    atSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    atSkin.setScale(altura*0.15,altura*0.15);
    atualizarPosicaoSprite();
}

AT_ST::AT_ST(float sx, float sy, float velx, float vely, int numVidas, int nivelMal):
    Inimigo(),
    Thread(),
    altura(1),
    directionMove(true),
    pProj(NULL),
    alvo1(NULL),
    alvo2(NULL)
{
    derivadoThread=true;
    
    num_vidas = numVidas;
    vidaMax = 20;
    nivel_maldade = nivelMal;

    x = sx;
    y = sy;
    velocidade.x = velx;
    velocidade.y = vely;

    pTexturaAT = pGG->carregarTextura(ATPNG);
    pTexturaDanoAT = pGG->carregarTextura(ATDANOPNG);

    if (pTexturaAT == NULL || pTexturaDanoAT == NULL)
        cerr << "Erro de carregamento do PNG do AT-ST" << endl;
    else
        atSkin.setTexture(*pTexturaAT); 

    sf::FloatRect bounds = atSkin.getLocalBounds();
    atSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    atSkin.setScale(altura*0.15,altura*0.15);
    atualizarPosicaoSprite();
    atualizarBarraVida();
}

AT_ST::~AT_ST()
{
    num_vidas = -1;
}

void AT_ST::executar()
{
    start();
    join();
    /*
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

        this->operator++();
    }

    if (y + (getBounds().height/2.0f) > 700)
    {
        if (directionMove)
            velocidade.x = 100.0f;
        else
            velocidade.x = -100.0f;
    }

    if((!(pProj->getAtivo())) && clockTiro.getElapsedTime().asSeconds()>=6.0f)
        atirar();

    aplicarFisica();
    mover();
    */
}

void AT_ST::danificar(Jogador* p)
{
    int chance = rand()%10; 
    if (num_vidas && chance>3)
    {
        p->sofrerAtaque(nivel_maldade/3);
    }
}

sf::Sprite AT_ST::getDrawData() const
{
    return atSkin;
}

sf::FloatRect AT_ST::getBounds() const
{
    return atSkin.getGlobalBounds();
}

void AT_ST::salvar()
{
    Inimigo::salvarDataBuffer();

    if (buffer != NULL)
    {
        *buffer << "AT_ST" << '%';
    }
}

void AT_ST::mover()
{
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velocidade.x * dt;
    y += velocidade.y * dt;

    atualizarPosicaoSprite();
}

void AT_ST::operator++()
{
    nivel_maldade += 4;
}

void AT_ST::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    atSkin.setPosition(x,y);
    atualizarPosicaoBarra();
}

sf::Vector2f AT_ST::calcularPontoAtirador() const
{
    const sf::FloatRect bounds = this->getBounds();

    return sf::Vector2f (x, y);
}

sf::Vector2f AT_ST::calcularPontoAlvo (const Jogador* pJog) const
{
    if (pJog == NULL)
        return calcularPontoAtirador();

    const sf::FloatRect boundsJog = pJog->getBounds();
    
    return sf::Vector2f(
        boundsJog.left + boundsJog.width / 2.0f,
        boundsJog.top + boundsJog.height / 2.0f
    );
}

sf::Vector2f AT_ST::calcularLancamento(const Jogador* pJog, float velocidadeLancamento) const
{
    if (pJog == NULL || velocidadeLancamento <= 0.0f)
        return calcularPontoAtirador();

    const sf::Vector2f origem = calcularPontoAtirador();
    const sf::FloatRect boundsJog = pJog->getBounds();

    sf::Vector2f alvo = calcularPontoAlvo(pJog);

    const float dx = alvo.x - origem.x;
    const float dy = alvo.y - origem.y;

    const float distancia = sqrt(dx * dx + dy * dy);
    const float tempoEstimado = distancia/velocidadeLancamento;

    const float quedaEstimativa = 0.5f * gravidade * tempoEstimado * tempoEstimado;   
    alvo.y -= quedaEstimativa; // Mira mais para cima

    return alvo;
}

void AT_ST::atirar()
{
    Jogador* lockAlvo;

    if (alvo2 == NULL)
        lockAlvo = alvo1;
    else
    {
        if(alvo1->getVida()<=0)
            lockAlvo = alvo2;
        else if (alvo2->getVida()<=0)
            lockAlvo = alvo1;
        else
        {
            if(rand()%2)
                lockAlvo = alvo1;
            else
                lockAlvo = alvo2;
        }
    }

    //cout<<"atirando"<<endl;
    pProj->perseguir(lockAlvo);
    clockTiro.restart();
}

void AT_ST::setProjetil(Projetil* pP)
{
    if(pP != NULL)
    {
        pP->setAT(this);
        pProj = pP;
    }
}

void AT_ST::setAlvos(Jogador* pJog1, Jogador* pJog2)
{
    alvo1 = pJog1;
    alvo2 = pJog2;
}

/*
void AT_ST::execThreadMutex()
{
    start();
    join();
}*/

void* AT_ST::run()
{
    lock();
    
    atualizarBarraVida();

    salvarPosicaoAnterior();
    
    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());
    velocidade.x = 0.0f;

    if ((atSkin.getTexture() == pTexturaDanoAT) && (textureClock.getElapsedTime().asMilliseconds() >= 150))
        atSkin.setTexture(*pTexturaAT);

    int chance = rand()%10;

    if (aleatMov.getElapsedTime().asSeconds() >= 2.0f)
    {   
        if (x - (getBounds().width/2.0f) < 10 && chance > 1)
            directionMove = true;
        else if (x + (getBounds().width/2.0f) > 1270 && chance > 1)
            directionMove = false;
        else if ((x > 640 && chance > 3)||(x < 640 && chance < 4))
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

    if((!(pProj->getAtivo())) && clockTiro.getElapsedTime().asSeconds()>=6.0f)
        atirar();

    aplicarFisica();
    mover();

    semaforoAberto=false;
    unlock();
    yield();
    return NULL;
}

void AT_ST::sofrerAtaque(int dano)
{
    num_vidas-=dano;
    atSkin.setTexture(*pTexturaDanoAT); 
    textureClock.restart();
}