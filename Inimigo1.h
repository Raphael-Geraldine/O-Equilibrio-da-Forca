#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Inimigo1 : public Inimigo
            {
                private:
                    short int vida;
                    float raio;

                public:
                    Inimigo1 ();
                    ~Inimigo1 ();
                    void executar();
                    void danificar(Jogador* p);
                    void salva();
                    void atirar();
                    void operator++(int);
            };
        }
    }
}