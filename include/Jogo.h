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
        class Gerenciador_Eventos;
        class Observador_Teclado;
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
        NomeJog1,
        NomeJog2,
        Jogando,
        Ranking,
        Pause,
        Carregar,
        ComoJogar
    };

    class Jogo
    {
        private:
            Estado estadoAtual;
            vector<sf::Text> textOptions;
            sf::Clock typingDelay;

            Gerenciadores::Gerenciador_Eventos* pGerEventos;
            Gerenciadores::Observador_Teclado* pObsTeclado;

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
            Jogo();
            ~Jogo();

            void executar();
            Fases::Fase* getFase() const;
            void inicializarJogo();
            void atualizarFase();
            void limparFase();
            string& getNome(short int n);

            void fecharJogo(sf::RenderWindow& janela);
            void atalhoSalvarESair(sf::RenderWindow& janela);
            
            void alternarPause();
            void voltarMenuPeloPause();
            void confirmarEntrada();
            void voltarParaMenu();
            
            void salvar();
            void salvarFechamento();
            void carregarSave();
            void carregarSaveMenu();
    };
}
