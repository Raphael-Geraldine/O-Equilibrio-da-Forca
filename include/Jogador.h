#pragma once

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Jogador : public Personagem
            {
                protected:
                    int pontos;

                public:
                    Jogador();
                    ~Jogador();
                    void colidirInimigo(Inimigo* pIn);
                    void colidirObstaculo(Obstaculo* pOb);
                    void executar();
                    void salvar();
                    void mover();
            };
        }
    }
}