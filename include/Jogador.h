#pragma once

#include "../include/Personagem.h"
#include "../include/Inimigo.h"

namespace OEquilibrioDaForca
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

                public:
                    Jogador();
                    Jogador(float sx,float sy,float velx,float vely,int numVidas,short int n,int pontos);
                    ~Jogador();
                    void colidirInimigo(Inimigo* pIn);
                    int getPontos() const;
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
