#pragma once

#include <vector>
#include <string>
using namespace std;

#include "../include/Estado.h"
using namespace OEquilibrioDaForca;

#include "../include/ListaEntidades.h"
#include "../include/Gerenciador_Eventos.h"
#include "../include/Observador_Teclado.h"
#include "../include/Observador_Menu.h"

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
    }
}

namespace OEquilibrioDaForca
{
    class Jogo
    {
        private:
            Estado::Tipo estadoAtual;
            vector<sf::Text> textOptions;
            sf::Clock typingDelay;

            Gerenciadores::Gerenciador_Eventos* pGerEventos;
            Gerenciadores::Observador_Teclado* pObsTeclado;
            Gerenciadores::Observador_Menu* pObsMenu;
            
            Gerenciadores::Gerenciador_Grafico* pGG;
            Menu* pMenu;
            OEquilibrioDaForca::Listas::ListaEntidades LEntidades;
            Fases::Fase* pFase;

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
