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
            class Stormtrooper : public Inimigo
            {
                private:
                    float altura;
                    sf::Sprite stormSkin;
                    bool directionMov;

                public:
                    Stormtrooper ();
                    Stormtrooper (float sx, float sy, float velx, float vely, int numVidas, int nivelMal);
                    ~Stormtrooper ();
                    void executar();
                    void danificar(Jogador* p);
                    sf::Sprite getDrawData() const;
                    sf::FloatRect getBounds() const;
                    void salvar();
                    void mover();
                    void atualizarPosicaoSprite();
            };
        }
    }
}
