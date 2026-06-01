#pragma once

#include "../include/ListaEntidades.h"
using namespace TrabalhoJogo;
using namespace Listas;

namespace TrabalhoJogo 
{ 
    class Menu;

    namespace Gerenciadores 
    { 
        class Gerenciador_Grafico;
    }

    namespace Entidades 
    { 
        namespace Personagens
        {
            class Jogador;
        }
    }

    namespace Fases 
    { 
        class Fase;
        class Mustafar;
        //class Hoth;
    }
}

namespace TrabalhoJogo
{
    class Principal
    {
        private:
            TrabalhoJogo::Menu* pMenu;
            TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* pGG;
            TrabalhoJogo::Listas::ListaEntidades LEntidades;
            // TrabalhoJogo::Entidades::Personagens::Jogador* pAnakin;
            // TrabalhoJogo::Entidades::Personagens::Jogador* pObiWan;
            TrabalhoJogo::Fases::Mustafar* pMustafar;
            //TrabalhoJogo::Fases::Hoth* hoth;

            TrabalhoJogo::Entidades::Personagens::Jogador* pAnakin;

        public:
            Principal();
            ~Principal();
            void executar();
    };
}