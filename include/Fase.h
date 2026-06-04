#pragma once

#include "../include/Lista.h"
#include "../include/ListaEntidades.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Plataforma.h"
#include "../include/Gerenciador_Colisoes.h"
#include "../include/Ente.h"

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

                Entidades::Personagens::Jogador* pJogador1;
                Entidades::Personagens::Jogador* pJogador2;
                Entidades::Obstaculos::Plataforma* pPlat;

                Listas::ListaEntidades listaEntidades;
                Listas::Lista<Entidades::Personagens::Jogador> listaJogadores;
                Listas::Lista<Entidades::Personagens::Inimigo> listaInimigos;
                Listas::Lista<Entidades::Obstaculos::Plataforma> listaPlataformas;

                Gerenciadores::Gerenciador_Colisoes* gC;

                const int minInimigosFaceis;
                const int maxInimigosFaceis;
                const int minPlat;
                const int maxPlat;
                
                sf::RectangleShape ground;

                void inicializar(Entidades::Personagens::Jogador* pJ1 = nullptr, 
                     Entidades::Personagens::Jogador* pJ2 = nullptr);

            private:
                void criarInimigosFaceis();
                void criarPlataformas(); //Obstáculo fácil
                virtual void criarInimigos() = 0;
                virtual void criarObstaculos() = 0;
                void criarCenario();
            
            public:
                Fase(Entidades::Personagens::Jogador* pJ1 = nullptr, 
                     Entidades::Personagens::Jogador* pJ2 = nullptr);

                ~Fase();

                virtual void incluirJogador(Jogador* pJ) = 0;
                virtual void incluirInimigo(Inimigo* pI) = 0;

                virtual void incluirEntidade (Entidade* pE) = 0;
                Listas::ListaEntidades* getListaEntidades();

                virtual void executar();

                virtual sf::Sprite getFundo() = 0;
                sf::RectangleShape getGround();
        };
    }
}