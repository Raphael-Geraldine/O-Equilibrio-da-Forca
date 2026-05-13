#pragma once

namespace TrabalhoJogo++
{
    namespace Entidades
    {
        class Projetil : public Ente
        {
            protected:
                bool ativo;

            public:
                Projetil();
                ~Projetil();
                void executar;
                void salvar;
        };
    }
}