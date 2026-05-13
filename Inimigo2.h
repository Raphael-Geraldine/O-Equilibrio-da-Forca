#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Inimigo2 : public Inimigo
            {
                private:
                    short int vida;
                    float tamanho;

                public:
                    Inimigo2 ();
                    ~Inimigo2 ();
                    void executar();
                    void danificar(Jogador* p);
                    void salva();
            };
        }
    }
}