#pragma once

namespace TrabalhoJogo++
{
    namespace Fase
    {
        class Guerra_dos_Clones : public Fase
        {
            private:
                const int maxInimigosMedios;

            protected:
                void criarInimigosMedios();
                void criarObstaculosMedios();
        };
    }
}