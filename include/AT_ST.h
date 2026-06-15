#pragma once

#include "../include/Entidade.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"

#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Entidades
    {

        class Projetil;

        namespace Personagens
        {
            class AT_ST : public Inimigo
            {
                private:
                    float altura;
                    sf::Sprite atSkin;
                    bool directionMov;
                    Projetil* pProj;
                    Jogador* alvo1;
                    Jogador* alvo2;
                    sf::Clock clockTiro;

                public:
                    AT_ST();
                    AT_ST(float sx, float sy, float velx, float vely, int numVidas, int nivelMal);
                    ~AT_ST();
                    void executar();
                    void danificar(Jogador* p);
                    sf::Sprite getDrawData() const;
                    sf::FloatRect getBounds() const;
                    void salvar();
                    void mover();
                    void operator++(); //aumentar o dano com pouca vida
                    void atualizarPosicaoSprite();
                    sf::Vector2f calcularPontoAlvo (const Jogador* pJog) const;
                    sf::Vector2f calcularPontoAtirador() const;
                    sf::Vector2f calcularLancamento(const Jogador* pJog, float velocidadeLancamento) const;
                    void atirar();
                    void setProjetil(Projetil* pP);
                    void setAlvos(Jogador* pJog1, Jogador* pJog2);
            };
        }
    }
}
