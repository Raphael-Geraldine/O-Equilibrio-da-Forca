#pragma once

#include "../include/Lista.h"
#include "../include/ListaEntidades.h"
#include "../include/K_2SO.h"
#include "../include/Inimigo.h"
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
                sf::Texture texturaFundo; 
                sf::Sprite fundo;

            private:
                void incluirEntidade(Entidade* pE);
                void incluirJogador(Jogador* pJ);
                void incluirInimigo(Inimigo* pI);
                void criarInimigos(); //Médios
                void criarObstaculos(); //Médios

            public:
                Mustafar(Entidades::Personagens::Jogador* pJ1 = nullptr, 
                         Entidades::Personagens::Jogador* pJ2 = nullptr);
                ~Mustafar();
                sf::Sprite getFundo();
        };
    }
}
