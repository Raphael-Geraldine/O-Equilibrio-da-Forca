#define ANAKINPNG "../assets/images/Anakin.png"
#define ANAKINDAMAGEPNG "../assets/images/AnakinDamage.png"
#define OBIWANPNG "../assets/images/ObiWan.png"
#define OBIWANDAMAGEPNG "../assets/images/ObiWanDamage.png"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "../include/Personagem.h"
#include "../include/Gerenciador_Grafico.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include "../include/Jogador.h"

short int Jogador::cont(0);

Jogador::Jogador(): Personagem(), nPlayer(cont++), pontos(0)
{
    num_vidas = 100;
    cooldownAtaque = 0.3f;
    
    skin.setScale(0.125f,0.125f);

    y=570;

    if (!nPlayer)
    {
        x=20;

        pTexturaJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINPNG);
        pTexturaDanoJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINDAMAGEPNG);

        if (pTexturaJogador == NULL || pTexturaDanoJogador == NULL)
            cerr << "Erro de carregamento do PNG do Jogador 1 (Anakin)" << endl;

        else
            skin.setTexture(*pTexturaJogador); 
    }
    else
    {
        x=100;

        pTexturaJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(OBIWANPNG);
        pTexturaDanoJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(OBIWANDAMAGEPNG);

        if (pTexturaJogador == NULL || pTexturaDanoJogador == NULL)
            cerr << "Erro de carregamento do PNG do Jogador 2 (Obi Wan)" << endl;

        else
            skin.setTexture(*pTexturaJogador); 
    }

    sf::FloatRect bounds = skin.getLocalBounds();
    skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    
    atualizarPosicaoSprite();
}

Jogador::Jogador(float sx,float sy,float velx,float vely,int numVidas,short int n,int pontos): Personagem(), nPlayer(cont++), pontos(pontos)
{
    num_vidas = numVidas;
    cooldownAtaque = 0.3f;

    x=sx;
    y=sy;
    velocidade.x = velx;
    velocidade.y = vely;
    
    skin.setScale(0.125f,0.125f);

    if (!nPlayer)
    {
        pTexturaJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINPNG);
        pTexturaDanoJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINDAMAGEPNG);

        if (pTexturaJogador == NULL || pTexturaDanoJogador == NULL)
            cerr << "Erro de carregamento do PNG do Jogador 1 (Anakin)" << endl;

        else
            skin.setTexture(*pTexturaJogador); 
    }
    else
    {
        pTexturaJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(OBIWANPNG);
        pTexturaDanoJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(OBIWANDAMAGEPNG);

        if (pTexturaJogador == NULL || pTexturaDanoJogador == NULL)
            cerr << "Erro de carregamento do PNG do Jogador 2 (Obi Wan)" << endl;

        else
            skin.setTexture(*pTexturaJogador); 
    }

    sf::FloatRect bounds = skin.getLocalBounds();
    skin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    
    atualizarPosicaoSprite(); 
}

Jogador::~Jogador()
{
    pontos=-1;
    cont=0;
}

sf::Sprite Jogador::getDrawData() const
{
    return skin;
}

void Jogador::executar()
{
    salvarPosicaoAnterior();
    
    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());
    velocidade.x = 0.0f;
    
    if ((skin.getTexture() == pTexturaDanoJogador) && (textureClock.getElapsedTime().asMilliseconds() >= 150))
        skin.setTexture(*pTexturaJogador);

    if (!nPlayer)
    {
        // Para a esquerda.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocidade.x = -400.0f;

        // Para a direita.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocidade.x = 400.0f;

        // Para pular.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            pular();
    }
    else
    {
        // Para a esquerda.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocidade.x = -400.0f;

        // Para a direita.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocidade.x = 400.0f;

        // Para pular.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pular();
    }

    aplicarFisica();
    
    mover();
}
void Jogador::salvar()
{
    Personagem::salvarDataBuffer();

    if (buffer != NULL)
        *buffer << nPlayer << ' ' << pontos << ' '<< "Jogador" <<'%';
}

void Jogador::mover()
{
    deslocar(velocidade.x,velocidade.y);
}

void Jogador::deslocar(float velx, float vely)
{
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velx * dt;
    y += vely * dt;

    atualizarPosicaoSprite();
}

sf::FloatRect Jogador::getBounds() const
{
    return skin.getGlobalBounds();
}

void Jogador::colidirInimigo(Inimigo* pIn)
{
    if (getVida()>0)
    {
        if (!nPlayer)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && ((clockAtaque.getElapsedTime().asSeconds())>cooldownAtaque))
            {
                pIn->sofrerAtaque(5);
                if (pIn->getVida() <= 0)
                    pontos++;
                clockAtaque.restart();
            }
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && ((clockAtaque.getElapsedTime().asSeconds())>cooldownAtaque))
            {
                pIn->sofrerAtaque(5);
                if (pIn->getVida() <= 0)
                    pontos++;
                clockAtaque.restart();
            }
        }
    }
}

void Jogador::sofrerAtaque(int dano)
{
    num_vidas-=dano;
    skin.setTexture(*pTexturaDanoJogador); 
    textureClock.restart();
}

void Jogador::atualizarPosicaoSprite() 
{
    skin.setPosition(x,y);
}

int Jogador::getPontos() const
{
    return pontos;
}