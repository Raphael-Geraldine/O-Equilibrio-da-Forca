#pragma once

#include "Lista.h"

namespace TrabalhoJogo
{
    namespace Lista
    {
        class ListaEntidades
        {
            private:
                Lista<Entidade> LEs;

            public:
                ListaEntidades();
                ~ListaEntidades();
                void incluir(Entidade* pE);
                void percorrer();
        };
    }
}
