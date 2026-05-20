#pragma once

#include "../include/Fase.h"
using namespace TrabalhoJogo;
using namespace Fases;

namespace TrabalhoJogo
{
    namespace Fases
    {
        class Mustafar : public Fase
        {
            private:
                const int minInimigosMedios;
                const int maxInimigosMedios;

            protected:
                void criarInimigos(); //Médios
                void criarObstaculos(); //Médios

            public:
                Mustafar();
                ~Mustafar();
        };
    }
}
