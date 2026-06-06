#pragma once

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    // Forward declaration:
    namespace Gerenciadores
    {
        class Gerenciador_Grafico;
    }

    class Ente
    {
        protected:
            static int cont;
            int id;

            static Gerenciadores::Gerenciador_Grafico* pGG;
            //Figura* pFig;

        public:
            Ente();
            virtual ~Ente();
            virtual void executar() = 0;
            void desenhar();
            static void staticSetGG(Gerenciadores::Gerenciador_Grafico* pG);
            virtual sf::Sprite getDrawData() = 0;
    };
}
