#pragma once

#include "../include/Observador.h"

namespace OEquilibrioDaForca 
{
    class Jogo;

    namespace Gerenciadores 
    {
        class Observador_Teclado: public Observador
        {
            private:
                Jogo* pJogo;

            public:
                Observador_Teclado();
                ~Observador_Teclado();

                void setJogo (Jogo* pJ);
                void atualizar (const sf::Event& evento, sf::RenderWindow& janela);
        };
    }
}

