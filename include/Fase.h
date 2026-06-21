#pragma once

#include "../include/Lista.h"
#include "../include/ListaEntidades.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Plataforma.h"
#include "../include/Obstaculo.h"
#include "../include/Projetil.h"
#include "../include/Gerenciador_Colisoes.h"
#include "../include/Ente.h"

#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Fases
    {
        class Fase : public Ente
        {
            protected:
                short int entsAlive;
                short int nJogs;
                static short int platGeradas;

                Entidades::Personagens::Jogador* pJogador1;
                Entidades::Personagens::Jogador* pJogador2;

                Listas::ListaEntidades listaEntidades;
                Gerenciadores::Gerenciador_Colisoes* gC;

                const int minInimigosFaceis;
                const int maxInimigosFaceis;
                const int minPlat;
                const int maxPlat;
                
                sf::Sprite fundo;
                sf::RectangleShape chao;

            protected:   
                void inicializar(Entidades::Personagens::Jogador* pJ1 = NULL, 
                                 Entidades::Personagens::Jogador* pJ2 = NULL);
                void criarInimigosFaceis();
                void criarPlataformas(); //Obstáculo fácil
                void criarCenario();

                virtual void criarInimigos() = 0;
                virtual void criarObstaculos() = 0;
            
            public:
                Fase();

                virtual ~Fase();

                Listas::ListaEntidades* getListaEntidades();

                virtual void executar();

                virtual sf::Sprite getDrawData() const = 0;
                void increaseInimVivos();
                short int getInimVivos() const;
                short int numJogsVivos() const;
                sf::RectangleShape getChao() const;

                void increasePlatGeradas();

                void incluirGCInimigo(Entidades::Personagens::Inimigo* pInim);
                void incluirGCObstaculo(Entidades::Obstaculos::Obstaculo* pObs);
                void incluirGCProjetil(Projetil* pProj);

                void incluirEntidade(Entidades::Entidade* pE);
        };
    }
}