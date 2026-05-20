#pragma once

#include "../include/Entidade.h"
using namespace TrabalhoJogo;
using namespace Entidades;

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

namespace TrabalhoJogo
{
    namespace Gerenciadores
    {
        class Gerenciador_Colisoes
        {
            private:
                //vector<Inimigo*> LIs;
                //list<Obstaculo*> LOs;
                //set<Projetil*> LPs;
                Jogador* pAnakin;
                Jogador* pObiWan;

            private:
                const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
                void tratarColisoesJogsObstaculos();
                void tratarColisoesJogsInimigos();
                void tratarColisoesJogsProjeteis();
                void caracterOutOfBounds(Entidade* pe);

            public:
                Gerenciador_Colisoes(Jogador* pJ);
                ~Gerenciador_Colisoes();
                //void incluirInimigo(Inimigo* pi);
                //void incluirObstaculo(Obstaculo* po);
                //void incluirProjetil(Projetil* pj);

                //por enquanto estará na construtora
                //void setJog1 (Jogador* pJ);
                //void setJog2 (Jogador* pJ);

                void executar();
        };
    }
}
