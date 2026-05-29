#pragma once

#include <string>
#include <list>
#include <vector>
using namespace std;

#include <SFML/Graphics.hpp>


//Dá pra usar um tal de drawable, mais simples q o Sprite (assim tá ok, mas o outro é perfeccionismo)

namespace TrabalhoJogo
{
    class Menu;
    class Ente;

    namespace Fases
    {
        class Fase;
    }

    namespace Entidades
    {
        class Entidade;

        namespace Obstaculos
        {
            class Plataforma;
        }
    }
}

namespace TrabalhoJogo
{
    namespace Gerenciadores
    {

        using Fase = TrabalhoJogo::Fases::Fase;
        using Entidade = TrabalhoJogo::Entidades::Entidade;

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

                void window(Menu* pM, Fase* pF, Entidade* pEnt);
                
                void loadMenu(Menu* pM);
                void menuTextPlacement();
                void desenharTextoMenu (sf::RenderWindow & janela);
                void desenharMenu (Menu* pM, sf::RenderWindow & janela);

                void desenharFase(Fase* pF, sf::RenderWindow & janela, Entidade* pEnt);
                void posicionarEnte(Ente* pE);
                void desenharEnte (Ente* pE);
                void desenharOrigem(sf::RenderWindow& window, const sf::Sprite& sprite); //Apenas para debugar colisão
        };
    }
}
