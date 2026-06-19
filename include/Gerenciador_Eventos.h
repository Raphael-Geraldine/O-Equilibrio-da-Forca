#pragma once

#include <list>
using namespace std;

#include <SFML/Graphics.hpp>

#include "../include/Observador_Eventos.h"

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
                list<Observador_Eventos*> observadores;
                sf::Event eventoAtual;
                sf::RenderWindow* pJanela;

            public:
                Gerenciador_Eventos();
                ~Gerenciador_Eventos();

                void anexar(Observador_Eventos* pObs); // Attach (Observer)
                void desanexar(Observador_Eventos* pObs); // Detach (Observer)
                void notificar(); // Notify()

                void setEvento (const sf::Event& evento, sf::RenderWindow* pJan);
                const sf::Event& getEvento() const;
                sf::RenderWindow* getJanela() const;

                void limpar();
        };
    }
}
