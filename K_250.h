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
                    const short int dano;
                    float tamanho;

                public:
                    K_250 ();
                    ~K_250 ();
                    void executar();
                    void danificar(Jogador* p);
                    void salvar();
                    void mover();
                    //void operator++(int);
            };
        }
    }
}