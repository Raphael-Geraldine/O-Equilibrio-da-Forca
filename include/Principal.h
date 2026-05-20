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
            TrabalhoJogo::Menu* menu;
            TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* gG;
            TrabalhoJogo::Entidades::Personagens::Jogador* anakin;
            TrabalhoJogo::Entidades::Personagens::Jogador* obiWan;
            TrabalhoJogo::Fases::Mustafar* mustafar;
            //TrabalhoJogo::Fases::Hoth* hoth;

        public:
            Principal();
            ~Principal();
            void executar();
    };
}