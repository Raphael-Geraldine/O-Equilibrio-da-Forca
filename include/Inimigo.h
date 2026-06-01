#pragma once

#include "../include/Personagem.h"
#include "../include/Jogador.h"

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Inimigo : public Personagem
            {
                protected:
                    int nivel_maldade;

                public:
                    Inimigo();
                    ~Inimigo();
                    void salvarDataBuffer();
                    virtual void danificar(Jogador* p);
                    virtual sf::Sprite getDrawData() = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    virtual void mover() = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
            };
        }
    }
}
