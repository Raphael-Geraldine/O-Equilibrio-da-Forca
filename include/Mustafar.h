#pragma once

#include "../include/Lista.h"
#include "../include/ListaEntidades.h"
#include "../include/K_2SO.h"
#include "../include/Inimigo.h"
#include "../include/Obstaculo.h"
#include "../include/Gerenciador_Colisoes.h"
#include "../include/Ente.h"
#include "../include/Fase.h"

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Fases
    {
        class Mustafar : public Fase
        {
            private:
                const int minInimigosMedios;
                const int maxInimigosMedios;
                const int minObstMedios;
                const int maxObstMedios;
                sf::Texture texturaFundo; 
                sf::Sprite fundo;

            private:
                //void incluirEntidade(Entidades::Entidade* pE);
                //void incluirJogador(Entidades::Personagens::Jogador* pJ);
                //void incluirInimigo(Entidades::Personagens::Inimigo* pI);
                //void incluirObstaculo(TrabalhoJogo::Entidades::Obstaculos::Obstaculo* pO);
                void criarInimigos(); //Médios
                void criarObstaculos(); //Médios

            public:
                Mustafar(Entidades::Personagens::Jogador* pJ1 = nullptr, 
                         Entidades::Personagens::Jogador* pJ2 = nullptr);
                ~Mustafar();
                sf::Sprite getDrawData();
        };
    }
}
