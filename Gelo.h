#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Obstaculo
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