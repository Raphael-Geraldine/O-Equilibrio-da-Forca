#pragma once

namespace TrabalhoJogo
{
    namespace Entidades
    {
        class Projetil : public Ente
        {
            protected:
                bool ativo;
                short int dano;

            public:
                Projetil(short int d);
                ~Projetil();
                void executar();
                void salvar();
        };
    }
}