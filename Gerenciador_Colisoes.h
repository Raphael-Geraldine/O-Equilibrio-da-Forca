#pragma once

namespace TrabalhoJogo++
{
    namespace Gerenciadores
    {
        class Gerenciador_Colisoes
        {
            private:
                vector<Inimigo*> LIs;
                list<Obstaculo*> LOs;
                set<Project*> LPs;
                Jogador* pJog1;
                Jogador* pJog2;

            private:
                const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
                void tratarColisoesJogsObstaculos();
                void tratarColisoesJogsInimigos();
                void tratarColisoesJogsProjeteis();

            public:
                Gerenciador_Colisoes();
                ~Gerenciador_Colisoes();
                void incluirInimigo(Inimigo* pi);
                void incluirObstaculo(Obstaculo* po);
                void incluirProjetil(Projetil* pj);
                void executar();
        };
    }
}