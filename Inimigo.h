#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Inimigo : public Personagem
            {
                protected:
                    int nivel_maldade;

                public:
                    Inimigo();
                    ~Inimigo();
                    void salvarDataBuffer();
                    void mover();
                    virtual void danificar(Jogador* p);
                    virtual void executar() = 0
                    virtual void salvar() = 0
            };
        }
    }
}