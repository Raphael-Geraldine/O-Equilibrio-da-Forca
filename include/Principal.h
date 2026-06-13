#pragma once

#include <vector>
#include <string>
using namespace std;

#include "../include/ListaEntidades.h"

namespace TrabalhoJogo 
{ 
    class Menu;

    namespace Gerenciadores 
    { 
        class Gerenciador_Grafico;
    }

    namespace Entidades 
    { 
        namespace Personagens
        {
            class Jogador;
        }
    }

    namespace Fases 
    { 
        class Fase;
        //class Hoth;
    }
}

namespace TrabalhoJogo
{
    enum class Estado
    {
        Menu,
        Nomejog1,
        Nomejog2,
        Jogando,
        Ranking,
        Carregar,
        Comojogar
    };

    class Principal
    {
        private:
            Estado estadoAtual;
            vector<sf::Text> textOptions;
            sf::Clock typingDelay;

            Gerenciadores::Gerenciador_Grafico* pGG;
            Menu* pMenu;
            TrabalhoJogo::Listas::ListaEntidades LEntidades;
            // TrabalhoJogo::Entidades::Personagens::Jogador* pAnakin;
            // TrabalhoJogo::Entidades::Personagens::Jogador* pObiWan;
            Fases::Fase* pFase;
            //TrabalhoJogo::Fases::Hoth* hoth;

            Entidades::Personagens::Jogador* pAnakin1;
            Entidades::Personagens::Jogador* pObi1;
            string nomeJog1;
            string nomeJog2;

        public:
            Principal();
            ~Principal();

            void executar();
            Fases::Fase* getFase() const;
            void inicializarJogo();
            void atualizarFase();
            string& getNome(short int n);
    };
}
