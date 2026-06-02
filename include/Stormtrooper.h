#pragma once

#include "../include/Entidade.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Stormtrooper : public Inimigo
            {
                private:
                    short int vida;
                    float altura;
                    sf::Texture stormTexture;
                    sf::Sprite stormSkin;

                public:
                    Stormtrooper ();
                    ~Stormtrooper ();
                    void executar();
                    void danificar(Jogador* p);
                    sf::Sprite getDrawData();
                    sf::FloatRect getBounds() const;
                    void salvar();
                    void atacar();
                    void mover();
            };
        }
    }
}
