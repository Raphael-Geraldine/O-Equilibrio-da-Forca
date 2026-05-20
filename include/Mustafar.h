#pragma once

#include "../include/Fase.h"
using namespace TrabalhoJogo;
using namespace Fases;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

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
                Mustafar(Jogador* pJ); //parâmetro temp enquanto não há a lista
                ~Mustafar();
        };
    }
}
