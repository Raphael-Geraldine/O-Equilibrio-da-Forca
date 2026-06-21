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
        namespace Personagens
        {
            class K_2SO : public Inimigo
            {
                private:
                    float raioImpacto;
                    bool impactoAplicado;

                    sf::Texture* pTexturaK2;
                    sf::Texture* pTexturaDanoK2;
                    sf::Texture* pTexturaPoeiraK2;

                    // Salto e pouso pesado.
                    sf::Clock clockSalto;
                    sf::Clock clockImpacto;
                    sf::Clock maldadeClock;
                    float cooldownSalto;
                    float impulsaoSalto;

                    bool impactoAtivo;
                    float duracaoImpacto;

                private:
                    // Salto e pouso pesado.
                    void tentarPular();
                    void verificarImpacto();
                    void atualizarMaldade();

                public:
                    K_2SO ();
                    K_2SO (float sx, float sy, float velx, float vely, int numVidas, int nivelMal);
                    ~K_2SO ();

                    void sofrerAtaque(int dano);
                    void executar();
                    void danificar(Jogador* p);
                    bool getImpactoAtivo() const;
                    float getRaioImpacto() const;
                    int getDanoImpacto() const;
                    void consumirImpacto();

                    sf::Sprite getDrawData() const;
                    sf::FloatRect getBounds() const;

                    void mover();
                    void operator++(); //aumentar o nível de maldade e frequência de pulo com pouca vida
                    void atualizarPosicaoSprite();
                    void salvar();
                    void ativarImpacto();
                    void atualizarImpacto();
            };
        }
    }
}