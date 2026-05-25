#pragma once

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Obstaculo
        {
            class Plataforma : public Obstaculo
            {
                private:
                    float largura;
                    int altura;

                public:
                    Plataforma();
                    ~Plataforma();
                    void executar();
                    void salvar();
                    void obstaculizar(Jogador* p);
            };
        }
    }
}