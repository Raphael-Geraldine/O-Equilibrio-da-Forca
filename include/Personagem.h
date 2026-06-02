#pragma once

#include "../include/Entidade.h"
#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Personagem : public Entidade
            {
                protected:
                    int num_vidas;

                public:
                    Personagem(ID identificador = empty);
                    ~Personagem();
                    void salvarDataBuffer();
                    void gravity();
                    virtual sf::Sprite getDrawData() = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
                    virtual void mover() = 0;
            };
        }
    }
}