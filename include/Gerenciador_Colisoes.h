#pragma once

#include "../include/Entidade.h"
#include "../include/ListaEntidades.h"
#include "../include/Jogador.h"
#include "../include/Obstaculo.h"
#include "../include/Plataforma.h"
#include "../include/Inimigo.h"


#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Gerenciadores
    {
        using Listas::ListaEntidades;
        using Entidades::Entidade;
        using Entidades::Personagens::Jogador;
        using Entidades::Obstaculos::Plataforma;
        using Entidades::Obstaculos::Obstaculo;

        class Gerenciador_Colisoes
        {
            private:
                //ListaEntidades* pListaEntidades;
                Listas::Lista<Entidades::Personagens::Jogador>* pListaJogadores;
                Listas::Lista<Entidades::Obstaculos::Plataforma>* pListaPlataformas;
                Listas::Lista<Entidades::Personagens::Inimigo>* pListaInimigos;
                //Listas::Lista<Entidades::Projetil>* pListaProjeteis;

            private:
                const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
                void tratarColisoesJogsObstaculos(Jogador* pJog, Obstaculo* pPlat);
                void tratarColisoesJogsInimigos(Jogador* pJog, Inimigo* pInim);
                void tratarColisoesInimObstaculos(Inimigo* pInim, Plataforma* pPlat);
                void tratarColisoesJogsProjeteis();
                // void tratarColisaoJogadorPlataforma(Jogador* pJog, Plataforma* pPlat);
                void caracterOutOfBounds(Entidade* pe);

            public:
                Gerenciador_Colisoes(Listas::Lista<Entidades::Personagens::Jogador>* pLJ = nullptr,
                                     Listas::Lista<Entidades::Obstaculos::Plataforma>* pLP = nullptr,
                                     Listas::Lista<Entidades::Personagens::Inimigo>* pLI = nullptr);
                
                 ~Gerenciador_Colisoes();
                //void incluirInimigo(Inimigo* pI);
                //void incluirObstaculo(Obstaculo* pO);
                //void incluirProjetil(Projetil* pJ);

                //por enquanto estará na construtora
                //void setJog1 (Jogador* pJ);
                //void setJog2 (Jogador* pJ);

                void executar();
                
        };
    }
}
