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
                    bool noChao;
                    
                    float dt;
                    sf::Clock clockAtaque;

                    sf::Vector2f velocidade;

                    // Pensar em usar: constexpr é valor constante, conhecido em tempo de compilação.
                    static const float PIXELS_POR_METRO;
                    static const float GRAVIDADE_REAL;
                    static const float GRAVIDADE;
                    static const float VELOCIDADE_MAX_QUEDA;
                    static const float VELOCIDADE_PULO;

                public:
                    Personagem(ID identificador = empty);
                    ~Personagem();

                    void setDeltaTempo (const float tempo);
                    void setVelocidade (const sf::Vector2f vel);
                    void setVelocidadeX (const float vx);
                    void setVelocidadeY (const float vy);
                    sf::Vector2f getVelocidade() const;
                    
                    void setNoChao(const bool emChao);
                    bool getNoChao() const;

                    void salvarDataBuffer();
                    void gravity();
                    void pular();
                    int getVida();
                    virtual sf::Sprite getDrawData() = 0;
                    virtual sf::FloatRect getBounds() const = 0;
                    virtual void executar() = 0;
                    virtual void salvar() = 0;
                    virtual void mover() = 0;
            };
        }
    }
}