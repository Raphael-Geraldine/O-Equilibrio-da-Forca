#pragma once

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
            class Obstaculo : public Entidade
            {
                protected:
                    bool danoso;

                public:
                    Obstaculo();
                    ~Obstaculo();
                    void salvarDataBuffer();
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
                    virtual void mover() = 0;
                    virtual void obstaculizar(Jogador* p) = 0;
                    virtual sf::Sprite getDrawData()=0;
                    virtual sf::FloatRect getBounds() const = 0;
            };
        }
    }
}
