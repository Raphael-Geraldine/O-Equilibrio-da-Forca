#pragma once

#include <vector>
#include <string>
using namespace std;

#include "../include/ListaEntidades.h"
// #include "../include/ElemRank.h"

namespace OEquilibrioDaForca 
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

namespace OEquilibrioDaForca
{
    enum class Estado
    {
        Menu,
        Nomejog1,
        Nomejog2,
        Jogando,
        Ranking,
        Pause,
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
            OEquilibrioDaForca::Listas::ListaEntidades LEntidades;
            // OEquilibrioDaForca::Entidades::Personagens::Jogador* pAnakin;
            // OEquilibrioDaForca::Entidades::Personagens::Jogador* pObiWan;
            Fases::Fase* pFase;
            //OEquilibrioDaForca::Fases::Hoth* hoth;

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
            void limparFase();
            string& getNome(short int n);

            void salvar();
            void carregarSave();
    };
}
