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
                    
                    sf::Clock clockAtaque;
                    sf::Vector2f posicaoAnterior;

                    // Pensar em usar: constexpr é valor constante, conhecido em tempo de compilação.
                    static const float velocidadePulo;

                public:
                    Personagem();
                    ~Personagem();

                    void setDeltaTempo (const float tempo);
                    void setVelocidade (const sf::Vector2f vel);
                    void setVelocidadeX (const float vx);
                    void setVelocidadeY (const float vy);
                    sf::Vector2f getVelocidade() const;
                    
                    void setNoChao(const bool emChao);
                    bool getNoChao() const;
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