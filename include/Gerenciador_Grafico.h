#pragma once

#include <string>
#include <list>
#include <vector>
using namespace std;

#include <SFML/graphics.hpp>

namespace TrabalhoJogo
{
    class Menu;
    class Ente;

    namespace Fases
    {
        class Fase;
    }
}

namespace TrabalhoJogo
{
    namespace Gerenciadores
    {

        using Fase = TrabalhoJogo::Fases::Fase;

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

                void window(Menu* pM, Fase* pF);
                
                void loadMenu(Menu* pM);
                void menuTextPlacement();
                void desenharTextoMenu (sf::RenderWindow & janela);
                void desenharMenu (Menu* pM, sf::RenderWindow & janela);

                void desenharFase(Fase* pF, sf::RenderWindow & janela);
                void posicionarEnte(Ente* pE);
                void desenharEnte (Ente* pE);
        };
    }
}
