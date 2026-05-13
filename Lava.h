#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Obstaculo
        {
            class Lava : public Obstaculo
            {
                private:
                    short int danosidade;

                public:
                    Lava();
                    ~Lava();
                    void executar();
                    void salvar;
                    void obstaculizar (Jogador* p);
            };
        }
    }
}