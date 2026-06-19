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

                    int nivel_maldade;
                    float coolDownAtaque;
                    sf::Clock aleatMov;
                    bool directionMovee; //1 direita, 0 esquerda

                public:
                    Inimigo();
                    ~Inimigo();

                    void tentarDanificar(Jogador* pJ);
                    virtual void sofrerAtaque(int dano);
                    virtual void danificar(Jogador* pJ);
                    virtual sf::Sprite getDrawData() const = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    
                    void salvarDataBuffer();
                    virtual void mover() = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
            };
        }
    }
}
