#define ANAKINPNG "../assets/images/Anakin.png"

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

Jogador::Jogador(): Personagem(jogador), playerID(cont++)
{
    num_vidas = 100;
    
    playerSkin.setScale(0.125f,0.125f);

    x=20;
    y=570;

    if (!playerID)
    {
        sf::Texture* pTexturaJogador = Gerenciador_Grafico::getGerenciadorGrafico()->carregarTextura(ANAKINPNG);

        if (pTexturaJogador == nullptr)
            cerr << "Erro de carregamento do PNG do Jogador 1" << endl;

        else
            playerSkin.setTexture(*pTexturaJogador); 
    }
    else
        cout<<"Vai ser ObiWan"<<endl;

    sf::FloatRect bounds = playerSkin.getLocalBounds();
    playerSkin.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    
    playerSkin.setPosition(x,y);
}

Jogador::~Jogador()
{
    // TIRAR SEG: delete(playerSkin.getTexture());
}
sf::Sprite Jogador::getDrawData()
{

    return playerSkin;
}
void Jogador::executar()
{
    setDeltaTempo(Gerenciador_Grafico::getDeltaTempo());

    velocidade.x = 0.0f;
    
    // Para a esquerda.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocidade.x = -500.0f;

    // Para a direita.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocidade.x = 500.0f;

    // Para pular.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        pular();

    gravity();
    
    mover();

    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::F)))
        clockAtaque.restart();
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
    /*
    gravity();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        y-=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        y+=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        x+=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        x-=2;
    */

}

sf::FloatRect Jogador::getBounds() const
{
    return playerSkin.getGlobalBounds();
}

void Jogador::colidirInimigo(Inimigo* pIn)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && clockAtaque.getElapsedTime().asSeconds()<0.2f)
    {
        pIn->sofrerAtaque(10);
        y-=10; //recuo pós ataque, arrumar a física aqui tbm
        x-=20;
    }
}

void Jogador::sofrerAtaque(int dano)
{
    num_vidas-=dano;
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