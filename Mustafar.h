#pragma once

namespace TrabalhoJogo++
{
    namespace Fase
    {
        class Mustafar : public Fase
        {
            private:
                const int maxInimigosMedios;

            protected:
                void criarInimigosMedios();
                void criarObstaculosMedios();
        };
    }
}