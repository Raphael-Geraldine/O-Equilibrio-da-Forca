#pragma once

#include <vector>
using namespace std;

#include "../include/Obstaculo.h"
#include "../include/Jogador.h"

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Plataforma : public Obstaculo
            {
                private:
                    static short int cont;
                    static vector<sf::Vector2i> platPositions;
                    short int platID;
                    float largura;
                    sf::Texture platTexture;
                    sf::Sprite platSkin;
                    sf::IntRect platSize;

                public:
                    Plataforma(float l=0.0f);
                    ~Plataforma();
                    void executar();
                    void salvar();
                    void mover();
                    void obstaculizar(Jogador* pJog);
                    sf::Sprite getDrawData();
                    sf::FloatRect getBounds() const;
            };
        }
    }
}
