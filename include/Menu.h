#pragma once
#include <vector>
#include <string>
#include <list>
using namespace std;

#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca 
{ 
    namespace Gerenciadores 
    { 
        class Gerenciador_Grafico;
    }
}

#include "../include/Ente.h"
#include "../include/Jogador.h"
#include "../include/Jogo.h"
using namespace OEquilibrioDaForca;

namespace OEquilibrioDaForca
{  
    class Menu : public Ente
    {
        private:
            class ElemRank
            {
                private:
                    string nome;
                    int pontos;

                public:
                    ElemRank();
                    ElemRank(string n, int p);
                    ~ElemRank();

                    void setNome(string n);
                    void setPontos(int p);

                    string getNome() const;
                    int getPontos() const;   
            };

        private:
            Jogo* pJogo;

            short int faseEscolhida;
            short int qntdJogs;

            sf::Texture* pTexturaFundo;
            sf::Texture* pTexturaAnakin;
            sf::Sprite fundo;
            sf::Sprite anakin;

            sf::Font fonteMenu;

            sf::Texture* pTexturaNome1;
            sf::Texture* pTexturaNome2;
            sf::Sprite fundoNome;

            list<string> menuOptions;

            vector<ElemRank*> rank;
            sf::Sprite rankSprite;

            sf::Sprite howSprite;

            sf::Sprite pauseSprite;

        public:
            Menu();
            ~Menu();

            void executar();

            OEquilibrioDaForca::Estado::Tipo manager(sf::RenderWindow& janela, vector<sf::Text>& text);
            bool cliqueEmOpcao(sf::RenderWindow& janela, sf::Text& text);

            void loadMenu(vector<sf::Text>& text);
            void menuTextPlacement(vector<sf::Text>& textToDisplay);

            sf::Sprite getFundo() const;
            sf::Sprite getDrawData() const;
            sf::Sprite getNomeBack(short int n);

            short int getFaseEscolhida() const;
            short int getJogsEscolhido() const;

            void setFaseEscolhida(short int f, vector<sf::Text>& text);
            void setJogsEscolhido(short int j, vector<sf::Text>& text);

            void salvarRank(int pontos, string nome);
            void limparRank();

            size_t getTamanhoRank() const;
            string getNomeRank (int indice) const;
            int getPontosRank (int indice) const;
            vector<string> getLinhasRank() const;

            sf::Sprite& getRankSprite();
            sf::Sprite& getMenuPause();
            sf::Sprite& getHowSprite();

            void prepararTelaNome();
            void alternarFase(vector<sf::Text>& text);
            void alternarQuantidadeJogadores(vector<sf::Text>& text);
    };
}