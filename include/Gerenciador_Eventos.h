#pragma once

#include <SFML/Graphics.hpp>

#include "../include/Observado.h"

// Implementado segundo a referência bibliográfica 
// "Gang of Four Design Patterns", na seção que
// discorre sobre Observer - a partir da página 333 
// da edição consultada.

namespace OEquilibrioDaForca 
{
    namespace Gerenciadores 
    {
        class Gerenciador_Eventos: public Observado
        {
            private:
                sf::Event eventoAtual;
                sf::RenderWindow* pJanela;

            public:
                Gerenciador_Eventos();
                virtual ~Gerenciador_Eventos();

                void setEvento (const sf::Event& evento, sf::RenderWindow* pJan);
                const sf::Event& getEvento() const;
                sf::RenderWindow* getJanela() const;
        };
    }
}
