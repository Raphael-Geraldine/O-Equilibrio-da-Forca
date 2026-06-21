#pragma once

#include "../include/Projetil.h"
#include "../include/Entidade.h"
#include "../include/Inimigo.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Obstaculo.h"
#include "../include/Plataforma.h"
#include "../include/Lista.h"
#include "../include/K_2SO.h"

#include <vector>
#include <list>
#include <set>

#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Gerenciadores
    {
        class Gerenciador_Colisoes
        {
            private:
                static const float lim_esq;
                static const float lim_dir;
                static const float lim_cima;
                static const float lim_baixo;
                static const float epsilonJanela;
                static const float coefRestTeto;

                std::vector<Entidades::Personagens::Inimigo*> LIs;
                std::list<Entidades::Obstaculos::Obstaculo*> LOs;
                std::set<Entidades::Projetil*> LPjs;

                Entidades::Personagens::Jogador* pJog1;
                Entidades::Personagens::Jogador* pJog2;

                sf::RectangleShape* pChao;                

            private:
                bool verificarColisao(Entidades::Entidade* pE1, 
                Entidades::Entidade* pE2) const;
                
                // Colisões Jogadores
                void tratarColisoesJogsObstaculos();
                void tratarColisoesJogsInimigos();
                void tratarColisoesJogsProjeteis();
                void tratarColisoesChaoJogadores();

                // Colisões Inimigos:
                void tratarColisoesInimObstaculos();
                // void tratarColisoesInimProjeteis();
                void tratarColisoesChaoInimigos();

                // Colisão entre cada par:tratarColisao
                void tratarColisaoJogObstaculo(Entidades::Personagens::Jogador* pJog, 
                                               Entidades::Obstaculos::Obstaculo* pObs);
  
                void tratarColisaoJogInimigo(Entidades::Personagens::Jogador* pJog,
                                             Entidades::Personagens::Inimigo* pInim);

                void tratarColisaoInimObstaculo(Entidades::Personagens::Inimigo* pInim,
                                                Entidades::Obstaculos::Obstaculo* pObs);

                void tratarColisaoJogProjetil(Entidades::Personagens::Jogador* pJog, 
                                               Entidades::Projetil* pProj);

                void tratarColisaoPersonagemChao(Entidades::Personagens::Personagem* pP);
                void verificarImpactoK2SO();
                bool personagemSobreObstaculo(Entidades::Personagens::Personagem* pP, Entidades::Obstaculos::Obstaculo* pObs);
                bool jogadorNoImpactoChaoK2(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::K_2SO* pK2);
                void aplicarImpactoK2EmPlataforma(Entidades::Personagens::K_2SO* pK2, Entidades::Obstaculos::Obstaculo* pObs);
                bool personagemSobreChao(Entidades::Personagens::Personagem* pP);

            public:
                Gerenciador_Colisoes();

                ~Gerenciador_Colisoes();
                 
                void incluirInimigo(Entidades::Personagens::Inimigo* pI);
                void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pO);
                void incluirProjetil(Entidades::Projetil* pJ);
                void incluirChao(sf::RectangleShape* pC);

                void setJog1 (Entidades::Personagens::Jogador* pJ1);
                void setJog2 (Entidades::Personagens::Jogador* pJ2);
                
                void removerInimigo(Entidades::Personagens::Inimigo* pI);
                void executar();
                void caracterOutOfBounds(Entidades::Entidade* pE);  
        };
    }
}