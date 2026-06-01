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
                Mustafar(Entidades::Personagens::Jogador* pJ1 = nullptr, 
                         Entidades::Personagens::Jogador* pJ2 = nullptr);
                ~Mustafar();
        };
    }
}
