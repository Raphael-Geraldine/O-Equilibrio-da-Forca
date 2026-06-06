#pragma once

#include "../include/ListaEntidades.h"

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
        //class Hoth;
    }
}

namespace TrabalhoJogo
{
    class Principal
    {
        private:
            Gerenciadores::Gerenciador_Grafico* pGG;
            Menu* pMenu;
            TrabalhoJogo::Listas::ListaEntidades LEntidades;
            // TrabalhoJogo::Entidades::Personagens::Jogador* pAnakin;
            // TrabalhoJogo::Entidades::Personagens::Jogador* pObiWan;
            Fases::Fase* pFases[2];
            //TrabalhoJogo::Fases::Hoth* hoth;

            Entidades::Personagens::Jogador* pAnakin;

        public:
            Principal();
            ~Principal();

            void executar();
    };
}