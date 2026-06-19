#pragma once

#include <list>
using namespace std;

#include <SFML/Graphics.hpp>

#include "../include/Observador.h"

// Implementado segundo a referência bibliográfica 
// "Gang of Four Design Patterns", na seção que
// discorre sobre Observer - a partir da página 333 
// da edição consultada.

namespace OEquilibrioDaForca 
{
    namespace Gerenciadores 
    {
        class Gerenciador_Eventos
        {
            private:
                list<Observador*> observadores;

            public:
                Gerenciador_Eventos();
                ~Gerenciador_Eventos();

                void anexar(Observador* pObs); // attach (Observer o)
                void desanexar(Observador* pObs); // detach (Observer o)
                void notificar(const sf::Event& evento, sf::RenderWindow& janela); // notify()
                void limpar();
        };
    }
}
