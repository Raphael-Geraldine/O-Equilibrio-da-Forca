#pragma once

namespace TrabalhoJogo
{
    namespace Gerenciadores
    {
        class Gerenciador_Grafico;
    }
}

namespace TrabalhoJogo
{
    class Ente
    {
        protected:
            static int cont;
            int id;
            static TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* pGG;
            //Figura* pFig;

        public:
            Ente();
            virtual ~Ente();
            virtual void executar() = 0;
            void desenhar();
            void staticSetGG(TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* pG);
    };
}
