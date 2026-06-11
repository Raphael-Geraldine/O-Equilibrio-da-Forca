#pragma once

#include "../include/Personagem.h"
#include "../include/Inimigo.h"

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Jogador : public Personagem
            {
                protected:
                    static short int cont;
                    short int nPlayer; 
                    int pontos;
                    sf::Texture* pTexturaJogador;
                    sf::Texture* pTexturaDanoJogador;
                    sf::Sprite playerSkin;
                    sf::Clock textureClock;

                public:
                    Jogador();
                    ~Jogador();
                    void colidirInimigo(Inimigo* pIn);
                    int getPontos() const;
                    //void colidirObstaculo(Obstaculo* pOb);
                    sf::FloatRect getBounds() const;
                    sf::Sprite getDrawData() const;
                    void sofrerAtaque(int dano);
                    void executar();
                    void salvar();
                    void mover();
                    void deslocar(float velx, float vely);

                    void atualizarPosicaoSprite();
            };
        }
    }
}
