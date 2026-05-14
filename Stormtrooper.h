#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Stormtrooper : public Inimigo
            {
                private:
                    short int vida;
                    float raio;

                public:
                    Stormtrooper ();
                    ~Stormtrooper ();
                    void executar();
                    void danificar(Jogador* p);
                    void salva();
                    void atirar();
                    void mover();
                    void operator++(int);
            };
        }
    }
}