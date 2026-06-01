#pragma once

#include "../include/ListaEntidades.h"
#include "../include/Jogador.h"
#include "../include/Gerenciador_Colisoes.h"
#include "../include/Ente.h"
#include "../include/Plataforma.h"

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Fases
    {
        class Fase : public Ente
        {
            protected:
                static short int cont; //acho que essa lógica não vá funcionar, mas por enquanto tá assim para testes
                short int nFase;

                Listas::ListaEntidades listaEntidades;
                Entidades::Obstaculos::Plataforma* pPlat;

                Gerenciadores::Gerenciador_Colisoes* gC;

                const int minInimigosFaceis;
                const int maxInimigosFaceis;
                
                sf::Texture texturaFundo; 
                sf::Sprite fundo;
                sf::RectangleShape ground;

            protected:
                void criarInimigosFaceis();
                void criarPlataformas(); //Obstáculo fácil
                virtual void criarInimigos() = 0;
                virtual void criarObstaculos() = 0;
                void criarCenario();
            
            public:
                Fase(Jogador* pJ = nullptr);
                ~Fase();

                void incluirEntidade (Entidades::Entidade* pE);
                Listas::ListaEntidades* getListaEntidades();

                virtual void executar();
                sf::Sprite getFundo();
                sf::RectangleShape getGround();
                sf::Sprite getPlataforma();
        };
    }
}
