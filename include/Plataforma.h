#pragma once

#include "../include/Obstaculo.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Plataforma : public Obstaculo
            {
                private:
                    float largura;
                    int altura;

                public:
                    Plataforma(float l=0.0f, int a=0);
                    ~Plataforma();
                    void executar();
                    void salvar();
                    void mover();
                    void obstaculizar(Jogador* p);
            };
        }
    }
}
