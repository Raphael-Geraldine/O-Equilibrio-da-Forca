#pragma once

#include "../include/Personagem.h"

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
                    short int playerID; 
                    int pontos;
                    sf::Texture playerTexture;
                    sf::Sprite playerSkin;

                public:
                    Jogador();
                    ~Jogador();
                    //void colidirInimigo(Inimigo* pIn);
                    //void colidirObstaculo(Obstaculo* pOb);
                    sf::FloatRect getBounds() const;
                    sf::Sprite getDrawData();
                    void executar();
                    void salvar();
                    void mover();
            };
        }
    }
}
