#pragma once

#include "../include/Personagem.h"

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Jogador;

            class Inimigo : public Personagem
            {
                protected:
                    float cooldownAtaque;
                    int nivel_maldade;

                public:
                    Inimigo();
                    ~Inimigo();
                    void salvarDataBuffer();
                    void sofrerAtaque(int dano);
                    void tentarDanificar(Jogador* pJ);
                    virtual void danificar(Jogador* pJ);
                    virtual sf::Sprite getDrawData() = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    virtual void mover() = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
            };
        }
    }
}
