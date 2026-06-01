#pragma once

#include "../include/Obstaculo.h"

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Gelo : public Obstaculo
            {
                private:
                    short int danosidade;
                    float largura;

                public:
                    Gelo();
                    ~Gelo();
                    void desacelerar();
                    void executar();
                    void salvar();
                    void salvarDataBuffer();
                    void obstaculizar(Jogador* p);
            };
        }
    }
}
