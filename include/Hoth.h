#pragma once

//#include "../include/AT_ST.h"
#include "../include/Lista.h"
#include "../include/ListaEntidades.h"
#include "../include/Inimigo.h"
#include "../include/Obstaculo.h"
#include "../include/Gerenciador_Colisoes.h"
#include "../include/Ente.h"
#include "../include/Fase.h"

namespace TrabalhoJogo
{
    namespace Fases
    {
        class Hoth : public Fase
        {
            private:
                const int minChefoes;
                const int maxChefoes;
                const int minObstDificil;
                const int maxObstDificil;
                sf::Texture texturaFundo; 
                sf::Sprite fundo;

            private:
                //void incluirEntidade(Entidades::Entidade* pE);
                //void incluirJogador(Entidades::Personagens::Jogador* pJ);
                //void incluirInimigo(Entidades::Personagens::Inimigo* pI);
                //void incluirObstaculo(TrabalhoJogo::Entidades::Obstaculos::Obstaculo* pO);
                void criarInimigos(); //Chefoes: Dificil
                void criarObstaculos(); //Dificil
                void criarProjeteis();

            public:
                Hoth(Entidades::Personagens::Jogador* pJ1 = nullptr, 
                     Entidades::Personagens::Jogador* pJ2 = nullptr);
                ~Hoth();
                sf::Sprite getDrawData() const;

        };
    }
}