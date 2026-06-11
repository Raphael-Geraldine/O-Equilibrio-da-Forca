#pragma once
#include <vector>
#include <string>
#include <list>
using namespace std;

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo 
{ 
    namespace Gerenciadores 
    { 
        class Gerenciador_Grafico;
    }
}

#include"../include/Ente.h"
#include "../include/Principal.h"
using namespace TrabalhoJogo;

namespace TrabalhoJogo
{
    class Menu : public Ente
    {
        private:
            Principal* pJogo;
            Gerenciadores::Gerenciador_Grafico* pGGraf;

            string faseString;
            string jogsString;
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

        public:
            Menu();
            ~Menu();
            void executar();
            TrabalhoJogo::Estado manager(sf::RenderWindow& janela, vector<sf::Text>& text);
            bool cliqueEmOpcao(sf::RenderWindow& janela, sf::Text& text);
            void loadMenu(vector<sf::Text>& text);
            void menuTextPlacement(vector<sf::Text>& textToDisplay);
            sf::Sprite getFundo() const;
            sf::Sprite getDrawData() const;
            sf::Sprite getNomeBack(short int n);
            short int getFaseEscolhida() const;
            short int getJogsEscolhido() const;
    };
}