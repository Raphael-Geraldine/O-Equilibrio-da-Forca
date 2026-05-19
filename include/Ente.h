#pragma once

namespace TrabalhoJogo
{
    class Ente
    {
        protected:
            int id;
            static Gerenciador_Grafico* pGG;
            Figura* pFig;

        public:
            Ente();
            virtual ~Ente();
            virtual void executar() = 0
            void desenhar();
            void staticSetGG(Gerenciador_Grafico* pG);
    };
}
