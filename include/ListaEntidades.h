#pragma once

#include "Lista.h"
#include "Entidade.h"

namespace TrabalhoJogo
{
    namespace Lista
    {
        class ListaEntidades
        {
            private:
                Lista<Entidades::Entidade> LEs;

            public:
                ListaEntidades();
                ~ListaEntidades();
                void incluir(Entidade* pE);
                void percorrer();
        };
    }
}
