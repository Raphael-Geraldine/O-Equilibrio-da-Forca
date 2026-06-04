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
            class K_2SO : public Inimigo
            {
                private:
                    float altura;
                    sf::Sprite k2Skin;

                public:
                    K_2SO ();
                    ~K_2SO ();
                    void executar();
                    void danificar(Jogador* p);
                    sf::Sprite getDrawData();
                    sf::FloatRect getBounds() const;
                    void salvar();
                    void mover();
                    void operator++(); //aumentar o dano com pouca vida
            };
        }
    }
}
