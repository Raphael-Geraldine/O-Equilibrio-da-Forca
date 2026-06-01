#pragma once

#include "../include/Entidade.h"
#include "../include/Jogador.h"
#include "../include/Plataforma.h"
using namespace Entidades;
using namespace Personagens;
using namespace Obstaculos;

#pragma once

#include <SFML/Graphics.hpp>

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
                Plataforma* pPlat;

            private:
                const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
                void tratarColisoesJogsObstaculos();
                void tratarColisoesJogsInimigos();
                void tratarColisoesJogsProjeteis();

            public:
                Gerenciador_Colisoes(Jogador* pJ = nullptr, Plataforma* pP = nullptr);
                ~Gerenciador_Colisoes();
                //void incluirInimigo(Inimigo* pI);
                //void incluirObstaculo(Obstaculo* pO);
                //void incluirProjetil(Projetil* pJ);

                //por enquanto estará na construtora
                //void setJog1 (Jogador* pJ);
                //void setJog2 (Jogador* pJ);

                bool executar();
                bool caracterOutOfBounds(Entidade* pe);
        };
    }
}
