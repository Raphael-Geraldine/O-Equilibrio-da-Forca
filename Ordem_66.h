#pragma once

namespace TrabalhoJogo++
{
    namespace Fase
    {
        class Ordem_66 : public Fase
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