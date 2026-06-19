#pragma once

#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Gerenciadores
    {
        class Observador
        {
            protected:
                Observador();
                
            public:
                virtual ~Observador();

                virtual void atualizar (const sf::Event& evento, sf::RenderWindow& janela) = 0;
        };
    }
}