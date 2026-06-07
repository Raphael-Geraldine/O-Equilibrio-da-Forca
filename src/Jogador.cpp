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
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;
using namespace Gerenciadores;

#include "../include/Jogador.h"

short int Jogador::cont(0);

Jogador::Jogador(): Personagem(), playerID(cont++)
{
    num_vidas = 100;
    
    playerSkin.setScale(0.125f,0.125f);

    y=570;

    if (!playerID)
    {
        x=20;

        pTexturaJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINPNG);
        pTexturaDanoJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINDAMAGEPNG);

        if (pTexturaJogador == nullptr || pTexturaDanoJogador == nullptr)
            cerr << "Erro de carregamento do PNG do Jogador 1 (Anakin)" << endl;

        else
            playerSkin.setTexture(*pTexturaJogador); 
    }
    else
    {
        x=100;

        pTexturaJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(OBIWANPNG);
        pTexturaDanoJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(OBIWANDAMAGEPNG);

        if (pTexturaJogador == nullptr || pTexturaDanoJogador == nullptr)
            cerr << "Erro de carregamento do PNG do Jogador 2 (Obi Wan)" << endl;

        else
            playerSkin.setTexture(*pTexturaJogador); 
    }

    sf::FloatRect bounds = playerSkin.getLocalBounds();
    playerSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    
    atualizarPosicaoSprite();
}

Jogador::~Jogador()
{
    
}

sf::Sprite Jogador::getDrawData()
{
    return playerSkin;
}

void Jogador::executar()
{
    salvarPosicaoAnterior();
    
    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());
    velocidade.x = 0.0f;
    
    if ((playerSkin.getTexture() == pTexturaDanoJogador) && (textureClock.getElapsedTime().asMilliseconds() >= 150))
        playerSkin.setTexture(*pTexturaJogador);

    if (!playerID)
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

    gravity();
    
    mover();

    if (!playerID)
    {
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::F)))
        clockAtaque.restart();
    }
    else
    {
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::L)))
        clockAtaque.restart();
    }
}
void Jogador::salvar()
{
    
}

void Jogador::mover()
{
    // Em FPS maior, o personagem anda mais rápido. Para 60 FPS:
    // 220 px/s * 0,0167 s/frame = 3,67 pixels por frame
    x += velocidade.x * dt;
    y += velocidade.y * dt;

    atualizarPosicaoSprite();
}

sf::FloatRect Jogador::getBounds() const
{
    return playerSkin.getGlobalBounds();
}

void Jogador::colidirInimigo(Inimigo* pIn)
{
    if (!playerID)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && clockAtaque.getElapsedTime().asSeconds()<0.2f)
        {
            pIn->sofrerAtaque(10);
            y-=10; //recuo pós ataque, arrumar a física aqui tbm
            x-=20;
        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && clockAtaque.getElapsedTime().asSeconds()<0.2f)
        {
            pIn->sofrerAtaque(10);
            y-=10; //recuo pós ataque, arrumar a física aqui tbm
            x-=20;
        }
    }
}

void Jogador::sofrerAtaque(int dano)
{
    num_vidas-=dano;
    playerSkin.setTexture(*pTexturaDanoJogador); 
    textureClock.restart();
    cout<<num_vidas<<endl;
}

void Jogador::atualizarPosicaoSprite() 
{
    //void sf::Transformable::setPosition(const Vector2f &position)	
    playerSkin.setPosition(x,y);
}
/*
void Jogador::colidirObstaculo(Obstaculo* pOb)
{

}*/