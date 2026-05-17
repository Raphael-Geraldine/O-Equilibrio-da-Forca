#pragma once
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
            
            public:
                Gerenciador_Grafico();
                ~Gerenciador_Grafico();
                //void desenharEnte (Ente* pE);
                void desenharMenu (Menu* pM);
        };
    }
}