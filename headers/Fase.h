#pragma once

namespace TrabalhoJogo
{
    namespace Fase
    {
        class Fase : public Ente
        {
            protected:
                ListaEntidades lista_ents;
                Gerenciador_Colisoes GC;

            protected:
                void criarInimigosFaceis();
                void criarPlataformas();
                virtual void criarInimigos = 0
                virtual void criarObstaculos = 0
                void criarCenario();
            
            public:
                Fase();
                ~Fase();
                virtual void executar();
        };
    }
}