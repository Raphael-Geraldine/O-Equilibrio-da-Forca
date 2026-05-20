#pragma once

namespace TrabalhoJogo 
{ 
    class Menu;

    namespace Gerenciadores 
    { 
        class Gerenciador_Grafico;
    }

    /*namespace Entidades 
    { 
        namespace Personagens
        {
            class Jogador;
        }
    }*/

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
            TrabalhoJogo::Fases::Fase* pF;
            //TrabalhoJogo::Entidades::Personagens::Jogador anakin;
            //TrabalhoJogo::Entidades::Personagens::Jogador obiWan;
            //TrabalhoJogo::Fase::Mustafar mustafar;
            //TrabalhoJogo::Fase::Hoth hoth;

        public:
            Principal();
            ~Principal();
            void executar();
    };
}