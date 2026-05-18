#pragma once

namespace TrabalhoJogo
{
    namespace Fase
    {
        class Hoth : public Fase
        {
            private:
                const int maxChefoes;

            protected:
                void criarChefoes();
                void criarObstaculosMedios();
                void criarProjeteis();

        };
    }
}