#pragma once

#include "../include/Personagem.h"

#include "SFML/Graphics.hpp"

namespace OEquilibrioDaForca
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Jogador;

            class Inimigo : public Personagem
            {
                protected:
                    sf::Clock aleatMov;
                    bool directionMov; //1 direita, 0 esquerda
                    int nivel_maldade;

                public:
                    Inimigo();
                    ~Inimigo();
                    void salvarDataBuffer();
                    void tentarDanificar(Jogador* pJ);
                    virtual void sofrerAtaque(int dano);
                    virtual void danificar(Jogador* pJ);
                    virtual sf::Sprite getDrawData() const = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    virtual void mover() = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
            };
        }
    }
}
