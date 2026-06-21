#define K2PNG "../assets/images/K-2SO.png"
#define K2DANOPNG "../assets/images/K-2SODamage.png"
#define K2DUSTPNG "../assets/images/K-2SODust.png"

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

K_2SO::K_2SO():
    Inimigo(),
    cooldownSalto(3.0f),
    impulsaoSalto(320.0f),
    impactoAtivo(false),
    duracaoImpacto(0.35f),
    raioImpacto(220.0f),
    impactoAplicado(false)
{
    directionMove = true;
    num_vidas = 10;
    vidaMax = num_vidas;
    nivel_maldade = 9;

    x = (rand() % 1101) + 100; // x: 100 a 1100 
    y = 200; 

    pTexturaK2 = pGG->carregarTextura(K2PNG);
    pTexturaDanoK2 = pGG->carregarTextura(K2DANOPNG);
    pTexturaPoeiraK2 = pGG->carregarTextura(K2DUSTPNG);

    if (pTexturaK2 == NULL || pTexturaDanoK2 == NULL || pTexturaPoeiraK2 == NULL)
        cerr << "Erro de carregamento do PNG do K-2SO" << endl;
    else
        skin.setTexture(*pTexturaK2); 

    sf::FloatRect bounds = skin.getLocalBounds();
    skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    skin.setScale(altura*0.15f, altura*0.15f);
    atualizarPosicaoSprite();
}

K_2SO::K_2SO(float sx, float sy, float velx, float vely, int numVidas, int nivelMal):
    Inimigo(),
    cooldownSalto(3.0f),
    impulsaoSalto(320.0f),
    impactoAtivo(false),
    duracaoImpacto(0.35f),
    raioImpacto(220.0f),
    impactoAplicado(false)
{
    directionMove = true;

    num_vidas = numVidas;
    vidaMax = 10;
    nivel_maldade = nivelMal;

    x = sx;
    y = sy;

    velocidade.x=velx;
    velocidade.y=vely;

    pTexturaK2 = pGG->carregarTextura(K2PNG);
    pTexturaDanoK2 = pGG->carregarTextura(K2DANOPNG);
    pTexturaPoeiraK2 = pGG->carregarTextura(K2DUSTPNG);

    if (pTexturaK2 == NULL || pTexturaDanoK2 == NULL || pTexturaPoeiraK2 == NULL)
        cerr << "Erro de carregamento do PNG do K-2SO" << endl;

    else
        skin.setTexture(*pTexturaK2); 

    sf::FloatRect bounds = skin.getLocalBounds();
    skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

    skin.setScale(altura*0.15f, altura*0.15f);
    atualizarPosicaoSprite();
    atualizarBarraVida();
}

K_2SO::~K_2SO()
{
    num_vidas=-1;
}

void K_2SO::ativarImpacto()
{
    if (impactoAtivo || impactoAplicado)
        return;

    impactoAtivo = true;
    impactoAplicado = false;
    clockImpacto.restart();
}

void K_2SO::executar()
{
    atualizarBarraVida();

    salvarPosicaoAnterior();
    
    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());
    
    atualizarMaldade();

    velocidade.x = 0.0f;

    if (((skin.getTexture() == pTexturaDanoK2) && (textureClock.getElapsedTime().asMilliseconds() >= 150)) 
        || 
        ((skin.getTexture() == pTexturaPoeiraK2) && (clockImpacto.getElapsedTime().asSeconds() >= 0.25f)))
    {
        skin.setTexture(*pTexturaK2);
    }

    int chance = rand() % 10;

    if (aleatMov.getElapsedTime().asSeconds() >= 2.0f)
    {   
        if (x - (getBounds().width/2.0f) < 10 && chance > 1)
            directionMove = true; // Dir

        else if (x + (getBounds().width/2.0f) > 1270 && chance > 1)
            directionMove = false; // Esq

        else if ((x>640 && chance > 3)||(x<640 && chance < 4))
            directionMove=false; // Esq

        else
            directionMove=true; // Dir

        aleatMov.restart();
    }

    if (y + (getBounds().height/2.0f) > 700)
    {
        float velBase = 100.0f;

        if (num_vidas <= 2)
            velBase = 145.0f;

        else if (num_vidas <= 4)
            velBase = 120.0f;

        if (directionMove)
            velocidade.x = velBase;
            
        else
            velocidade.x = -velBase;
    }

    tentarPular();
    aplicarFisica();
    mover();
    atualizarImpacto();
}

void K_2SO::danificar(Jogador* p)
{
    if (p == NULL)
        return;

    if (num_vidas <= 0)
        return;
        
    int chance = rand() % 10; 

    if (chance >3)
        p->sofrerAtaque(nivel_maldade/3);
}

sf::Sprite K_2SO::getDrawData() const
{
    return skin;
}

sf::FloatRect K_2SO::getBounds() const
{
    return skin.getGlobalBounds();
}

void K_2SO::salvar()
{
    Inimigo::salvarDataBuffer();

    if (buffer != NULL)
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
    if (nivel_maldade < 20)
        nivel_maldade+=2;
}

void K_2SO::atualizarPosicaoSprite() 
{
    skin.setPosition(x,y);
    atualizarPosicaoBarra();
}

void K_2SO::sofrerAtaque(int dano)
{
    num_vidas -= dano;
    skin.setTexture(*pTexturaDanoK2); 
    textureClock.restart();
}

void K_2SO::tentarPular()
{
    if (impactoAtivo)
        return;

    if (!getEmSuperficie())
        return;

    if (clockSalto.getElapsedTime().asSeconds() < cooldownSalto)
        return;

    velocidade.y = -impulsaoSalto;
    setEmSuperficie(false);

    impactoAplicado = false;
    
    clockSalto.restart();
}

void K_2SO::atualizarMaldade()
{   
    if (num_vidas <= 5)
    {
        cooldownSalto = 1.8f;
        
        if (nivel_maldade < 15)
            nivel_maldade = 15;
        
        if (maldadeClock.getElapsedTime().asSeconds() >= 1.0f)
        {
            this->operator++();
            maldadeClock.restart();
        }
    }
}

bool K_2SO::getImpactoAtivo() const
{
    return (impactoAtivo && !impactoAplicado);
}

float K_2SO::getRaioImpacto() const
{
    return raioImpacto;
}

int K_2SO::getDanoImpacto() const
{
    return nivel_maldade/4;
}

// Impedir que o dano aconteça mais vezes no mesmo pouso.
void K_2SO::consumirImpacto()
{
    impactoAplicado = true;
    impactoAtivo = false;

    if(clockSalto.getElapsedTime().asMilliseconds()>100)
        skin.setTexture(*pTexturaPoeiraK2);
}

void K_2SO::atualizarImpacto()
{
    if (impactoAtivo && clockImpacto.getElapsedTime().asSeconds() >= duracaoImpacto)
        impactoAtivo = false;
}