#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Obstaculo
        {
            class Fogo : public Obstaculo
            {
                private:
                    float largura;

                public:
                    Fogo();
                    ~Fogo();
                    void executar();
                    void salvar;
                    void obstaculizar(Jogador* p);
            };
        }
    }
}