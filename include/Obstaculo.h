#pragma once

#include "../include/Jogador.h"
#include "../include/Inimigo.h"
using namespace OEquilibrioDaForca;
using namespace Entidades;
using namespace Personagens;

#include "SFML/Graphics.hpp"

namespace OEquilibrioDaForca
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Obstaculo : public Entidade
            {
                protected:
                    bool danoso;
                    bool aplicarGravidade;
                    float largura;

                public:
                    Obstaculo();
                    ~Obstaculo();
                    void salvarDataBuffer();
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
                    virtual void mover() = 0;
                    virtual void obstaculizar(Jogador* p) = 0;
                    virtual void obstaculizarInim(Inimigo* pInim) = 0;
                    virtual sf::Sprite getDrawData() const = 0;
                    virtual sf::FloatRect getBounds() const = 0;
            };
        }
    }
}
