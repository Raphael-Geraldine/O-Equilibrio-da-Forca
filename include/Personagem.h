#pragma once

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Personagem : public Entidade
            {
                protected:
                    int num_vidas;

                public:
                    Personagem();
                    ~Personagem();
                    void salvarDataBuffer();
                    virtual void executar() = 0
                    virtual void salvar() = 0
                    virtual void mover() = 0
            };
        }
    }
}