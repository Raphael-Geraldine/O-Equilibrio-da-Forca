#pragma once

#include "../include/Ente.h"
using namespace TrabalhoJogo;

#include <SFML/graphics.hpp>

namespace TrabalhoJogo
{
    namespace Fases
    {
        class Fase : public Ente
        {
            protected:
                static short int cont;
                short int nFase;
                //ListaEntidades lista_ents;
                //Gerenciador_Colisoes GC;
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
                Fase();
                ~Fase();
                virtual void executar();
                sf::Sprite getFundo();
                sf::RectangleShape getGround();
        };
    }
}
