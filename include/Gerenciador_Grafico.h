#pragma once

#include <string>
#include <list>
#include <vector>
using namespace std;

#include "../include/Menu.h"
#include "../include/Ente.h"
#include "../include/Fase.h"
#include "../include/Mustafar.h"
#include "../include/Entidade.h"
#include "../include/Plataforma.h"
#include "../include/Gerenciador_Grafico.h"
using namespace TrabalhoJogo;
using namespace Fases;
using namespace Entidades;
using namespace Obstaculos;
using namespace Gerenciadores;

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
                static Gerenciador_Grafico* pGrafico; // static Singleton* Instance();

            protected:
                // Padrão de projeto Singleton 
                // (conhecido pelos vídeos do canal Gege++)
                Gerenciador_Grafico();  // Singleton();
            
            public:
                
                ~Gerenciador_Grafico();
                static Gerenciador_Grafico* getGerenciadorGrafico(); // static Singleton* _instance;

                void window(Menu* pM, Fase* pF);
                
                void loadMenu(Menu* pM);
                void menuTextPlacement();
                void desenharTextoMenu (sf::RenderWindow & janela);
                void desenharMenu (Menu* pM, sf::RenderWindow & janela);

                void desenharFase(Fase* pF, sf::RenderWindow & janela);
                void posicionarEnte(Ente* pE);
                void desenharEnte (Ente* pE);
                void desenharOrigem(sf::RenderWindow& window, const sf::Sprite& sprite); //Apenas para debugar colisão
        };
    }
}
