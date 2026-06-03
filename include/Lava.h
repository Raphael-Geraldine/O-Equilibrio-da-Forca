#pragma once

#include "../include/Jogador.h"
#include "../include/Obstaculo.h"

#include "SFML/Graphics.hpp"

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Lava : public Obstaculo
            {
                private:
                    float largura;
                    short int danosidade;
                    sf::Sprite lavaSkin;
                    sf::Texture lavaTexture;

                public:
                    Lava();
                    ~Lava();
                    void executar();
                    void salvar();
                    void obstaculizar (Jogador* p);
                    void mover();
                    sf::Sprite getDrawData();
                    sf::FloatRect getBounds() const;
            };
        }
    }
}
