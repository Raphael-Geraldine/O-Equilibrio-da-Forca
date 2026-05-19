#pragma once

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Obstaculo
        {
            class Obstaculo : public Entidade
            {
                protected:
                    bool danoso;

                public:
                    Obstaculo();
                    ~Obstaculo();
                    void salvarDataBuffer();
                    virtual void executar() = 0
                    virtual void salvar = 0
                    virtual void obstaculizar(Jogador* p) = 0
            };
        }
    }
}
