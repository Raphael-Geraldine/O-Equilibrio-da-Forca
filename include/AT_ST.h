#pragma once

#include "../include/Entidade.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Thread.h"

#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Entidades
    {

        class Projetil;

        namespace Personagens
        {
            class AT_ST : public Inimigo, Thread
            {
                private:
                    sf::Texture* pTexturaAT;
                    sf::Texture* pTexturaDanoAT;
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
                    void sofrerAtaque(int dano);
                    sf::Sprite getDrawData() const;
                    sf::FloatRect getBounds() const;
                    void salvar();
                    void mover();
                    void operator++(); //aumentar o nível de maldade quando acerta projétil
                    void atualizarPosicaoSprite();
                    sf::Vector2f calcularPontoAlvo (const Jogador* pJog) const;
                    sf::Vector2f calcularPontoAtirador() const;
                    sf::Vector2f calcularLancamento(const Jogador* pJog, float velocidadeLancamento) const;
                    void atirar();
                    void setProjetil(Projetil* pP);
                    void setAlvos(Jogador* pJog1, Jogador* pJog2);
                    void* run();
            };
        }
    }
}
