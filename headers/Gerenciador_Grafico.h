#pragma once

#include <string>
#include <list>
#include <vector>
using namespace std;

#include <SFML/graphics.hpp>

namespace TrabalhoJogo
{
    class Menu /*: public Ente*/; 
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
            
            public:
                Gerenciador_Grafico();
                ~Gerenciador_Grafico();
                //void desenharEnte (Ente* pE);
                void desenharMenu (Menu* pM);
                void menuTextPlacement(sf::Font& fonteMenu);
                void desenharTextoMenu (sf::RenderWindow & janela);
        };
    }
}