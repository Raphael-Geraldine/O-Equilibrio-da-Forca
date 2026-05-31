#pragma once

#include "Lista.h"
#include "Entidade.h"

namespace TrabalhoJogo
{
    namespace Listas
    {
        class ListaEntidades
        {
            private:
                Lista<Entidades::Entidade> LEs;

            public:
                ListaEntidades();
                ~ListaEntidades();

                void incluir(Entidades::Entidade* pE);
                void remover(Entidades::Entidade* pE);
                void remover(size_t indice);
                size_t getTamanho();
                void percorrer();

                // Também inspirada na implementação do Burda, 
                // vide vídeo 8 da playlist Tutorial Jogo SFM,
                // como no header "Lista.h", naturalmente.
                Entidades::Entidade* operator[](int indice);
        };
    }
}
