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
                    
                    void setNoChao(const bool emChao);
                    bool getNoChao() const;
                    void salvarPosicaoAnterior();
                    sf::Vector2f getPosicaoAnterior() const;

                    void salvarDataBuffer();
                    void pular();
                    int getVida();
                    virtual sf::Sprite getDrawData() = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
                    virtual void mover() = 0;
                    virtual void atualizarPosicaoSprite() = 0;
            };
        }
    }
}