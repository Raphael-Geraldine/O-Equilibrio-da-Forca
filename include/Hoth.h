#pragma once

#include "../include/AT_ST.h"
#include "../include/Projetil.h"
#include "../include/Lista.h"
#include "../include/ListaEntidades.h"
#include "../include/Inimigo.h"
#include "../include/Obstaculo.h"
#include "../include/Gerenciador_Colisoes.h"
#include "../include/Ente.h"
#include "../include/Fase.h"

namespace OEquilibrioDaForca
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

            private:
                void criarInimigos(); //Chefoes: Dificil
                void criarObstaculos(); //Obstáculo dificil
                void criarProjeteis(int qntd, AT_ST* pAT);

            public:
                Hoth(Entidades::Personagens::Jogador* pJ1 = NULL, 
                     Entidades::Personagens::Jogador* pJ2 = NULL);
                Hoth(Entidades::Personagens::Jogador* pJ1, 
                     Entidades::Personagens::Jogador* pJ2,
                     char c);
                ~Hoth();
                sf::Sprite getDrawData() const;

        };
    }
}