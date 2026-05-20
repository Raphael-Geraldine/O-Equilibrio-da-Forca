#pragma once

#include "../include/Personagem.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Jogador : public Personagem
            {
                protected:
                    static short int cont;
                    short int playerID; 
                    int pontos;

                public:
                    Jogador();
                    ~Jogador();
                    //void colidirInimigo(Inimigo* pIn);
                    //void colidirObstaculo(Obstaculo* pOb);
                    void setSkin();
                    void executar();
                    void salvar();
                    void mover();
            };
        }
    }
}
