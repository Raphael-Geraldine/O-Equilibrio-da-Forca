#pragma once

namespace TrabalhoJogo++
{
    class O_Equilibrio_da_Forca
    {
        private:
            Jogador* pAnakin;
            Jogador* pObiWan;
            Gerenciador_Grafico GG;

        public:
            O_Equilibrio_da_Forca();
            ~O_Equilibrio_da_Forca();
            void executar();
    };
}