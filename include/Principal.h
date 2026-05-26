#pragma once

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

        namespace Obstaculos
        {
            class Plataforma;
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
            TrabalhoJogo::Entidades::Personagens::Jogador* pAnakin;
            TrabalhoJogo::Entidades::Personagens::Jogador* pObiWan;
            TrabalhoJogo::Fases::Mustafar* pMustafar;
            TrabalhoJogo::Entidades::Obstaculos::Plataforma* pPlat;
            TrabalhoJogo::Entidades::Obstaculos::Plataforma* pPlat2;
            //TrabalhoJogo::Fases::Hoth* hoth;

        public:
            Principal();
            ~Principal();
            void executar();
    };
}