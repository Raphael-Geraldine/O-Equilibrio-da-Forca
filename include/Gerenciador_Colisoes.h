#pragma once

#include "../include/Entidade.h"
#include "../include/ListaEntidades.h"
#include "../include/Jogador.h"
#include "../include/Plataforma.h"


#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Gerenciadores
    {
        using Listas::ListaEntidades;
        using Entidades::Entidade;
        using Entidades::Personagens::Jogador;
        using Entidades::Obstaculos::Plataforma;
        
        class Gerenciador_Colisoes
        {
            private:
                ListaEntidades* pListaEntidades;

            private:
                const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
                void tratarColisoesJogsObstaculos(Jogador* pJog, Plataforma* pPlat);
                void tratarColisoesJogsInimigos();
                void tratarColisoesJogsProjeteis();
                // void tratarColisaoJogadorPlataforma(Jogador* pJog, Plataforma* pPlat);
                bool caracterOutOfBounds(Entidade* pe);

            public:
                Gerenciador_Colisoes(ListaEntidades* pLE = nullptr);
                ~Gerenciador_Colisoes();
                //void incluirInimigo(Inimigo* pI);
                //void incluirObstaculo(Obstaculo* pO);
                //void incluirProjetil(Projetil* pJ);

                //por enquanto estará na construtora
                //void setJog1 (Jogador* pJ);
                //void setJog2 (Jogador* pJ);

                bool executar();
                
        };
    }
}
