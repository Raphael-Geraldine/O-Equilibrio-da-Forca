#pragma once

#include "../include/Observador_Eventos.h"

namespace OEquilibrioDaForca 
{
    class Jogo;

    namespace Gerenciadores 
    {
        class Observador_Teclado: public Observador_Eventos
        {
            private:
                Jogo* pJogo;

            public:
                Observador_Teclado();
                ~Observador_Teclado();

                void setJogo (Jogo* pJ);
                void atualizar (Observado* pObservado);
        };
    }
}

