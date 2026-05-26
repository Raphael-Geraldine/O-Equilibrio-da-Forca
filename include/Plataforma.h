#pragma once

#include <vector>
using namespace std;

#include "../include/Obstaculo.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

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
                    void obstaculizar(Jogador* p);
                    sf::Sprite getDrawData();
                    sf::FloatRect getBounds() const;
            };
        }
    }
}
