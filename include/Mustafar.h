#pragma once

#include "../include/Fase.h"
#include "../include/Jogador.h"

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
