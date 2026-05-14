#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Personagens
        {
            class K_250 : public Inimigo
            {
                private:
                    short int vida;
                    float tamanho;

                public:
                    K_250 ();
                    ~K_250 ();
                    void executar();
                    void danificar(Jogador* p);
                    void salva();
                    void mover();
            };
        }
    }
}