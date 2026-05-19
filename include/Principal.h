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

    /*namespace Fase 
    { 
        class Mustafar;
        class Hoth;
    }*/
}

namespace TrabalhoJogo
{
    class Principal
    {
        private:
            TrabalhoJogo::Menu* menu;
            TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* gG;
            //Jogador anakin;
            //Jogador obiWan;
            //Mustafar mustafar;
            //Hoth hoth;

        public:
            Principal();
            ~Principal();
            void executar();
    };
}