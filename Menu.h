#pragma once

namespace TrabalhoJogo++
{
    class Menu : public Ente
    {
        private:
            O_Equilibrio_da_Forca* pJogo;

        public:
            Menu();
            ~Menu();
            void executar();

    };
}