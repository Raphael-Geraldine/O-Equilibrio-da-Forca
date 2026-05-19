#pragma once

#include <string>
#include <list>
#include <vector>
using namespace std;

#include <SFML/graphics.hpp>

namespace TrabalhoJogo
{
    class Menu; 
}

namespace TrabalhoJogo
{
    namespace Gerenciadores
    {
        class Gerenciador_Grafico
        {
            private:
                sf::RenderWindow janela;

                sf::Texture texturaFundo; 
                sf::Sprite fundo;

                sf::Font fonteMenu;

                sf::Texture texturaAnakin;
                sf::Sprite anakin;

                sf::Text textIniciar;
                sf::Text textRank;
                sf::Text textLoad;
                sf::Text textFase;
                sf::Text textPlayers;
                sf::Text textRules;

                list<string> menuOptions;
                vector<sf::Text> textOptions;
                static short int optionSelected;   
            
            public:
                Gerenciador_Grafico();
                ~Gerenciador_Grafico();
                //void desenharEnte (Ente* pE);
                void loadMenu(Menu* pM);
                void desenharMenu (Menu* pM, sf::RenderWindow & janela);
                void window(Menu* pM);
                void menuTextPlacement();
                void desenharTextoMenu (sf::RenderWindow & janela);
        };
    }
}
