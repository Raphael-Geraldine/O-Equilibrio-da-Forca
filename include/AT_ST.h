#pragma once

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class AT_ST : public Inimigo
            {
                private:
                    const short int altura;
                    short int dano;
                    short int vida;
                    short int forca;

                public:
                    AT_ST (short int v=100, short int f = 80);
                    ~AT_ST ();
                    void executar();
                    void danificar(Jogador* p);
                    void salvar();
                    void recuperarVida();
                    short int calculaRaio();
                    void soltarRaio();
                    void enfurecer();
                    void mover();
            };
        }
    }
}