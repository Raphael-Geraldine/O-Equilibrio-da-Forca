#pragma once

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class K_2SO : public Inimigo
            {
                private:
                    short int vida;
                    const short int dano;
                    float tamanho;

                public:
                    K_2SO ();
                    ~K_2SO ();
                    void executar();
                    void danificar(Jogador* p);
                    void salvar();
                    void mover();
                    //void operator++(int);
            };
        }
    }
}