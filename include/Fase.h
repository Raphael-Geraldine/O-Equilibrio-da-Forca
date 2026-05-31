#pragma once

#include "../include/Jogador.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Personagens;

#include "../include/Gerenciador_Colisoes.h"
using namespace TrabalhoJogo;
using namespace Gerenciadores;

#include "../include/Ente.h"
using namespace TrabalhoJogo;

#include "../include/Plataforma.h"
using namespace TrabalhoJogo;
using namespace Entidades;
using namespace Obstaculos;

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

                Jogador* pJog; //é pra virar isso depois: ListaEntidades lista_ents;
                Plataforma* pPlat;

                Gerenciador_Colisoes* gC;
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
                virtual void executar();
                sf::Sprite getFundo();
                sf::RectangleShape getGround();
                sf::Sprite getPlataforma();
        };
    }
}
