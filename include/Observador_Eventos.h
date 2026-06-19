#pragma once

#include "../include/Observado.h"
#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Gerenciadores
    {
        class Observador_Eventos
        {
            protected:
                Observador_Eventos();

            public:
                virtual ~Observador_Eventos();

                virtual void atualizar (Observado* pObservado) = 0;
        };
    }
}