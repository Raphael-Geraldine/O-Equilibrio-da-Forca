#pragma once

#include "../include/Entidade.h"
#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Personagem : public Entidade
            {
                protected:
                    int num_vidas;
                    float cooldownAtaque;
                    
                    sf::Clock clockAtaque;
                    sf::Vector2f posicaoAnterior;

                    sf::Clock textureClock;

                    static const float velocidadePulo;

                public:
                    Personagem();
                    ~Personagem();
                    
                    void setEmSuperficie(const bool naSuperficie);
                    bool getEmSuperficie() const;
                    void salvarPosicaoAnterior();
                    sf::Vector2f getPosicaoAnterior() const;

                    void salvarDataBuffer();
                    void pular();
                    int getVida();
                    virtual sf::Sprite getDrawData() const = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
                    virtual void mover() = 0;
                    virtual void atualizarPosicaoSprite() = 0;
            };
        }
    }
}