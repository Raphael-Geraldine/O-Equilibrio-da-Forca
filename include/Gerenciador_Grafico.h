#pragma once

#include <string.h>
#include <list>
#include <vector>
using namespace std;

#include <iostream>
#include <map>
using std::cout;
using std::cerr;
using std::endl;
using std::pair;
using std::map;


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

                // Funções conhecidas pelos vídeos do Burda:
                map<const char*, sf::Texture*> mapaTexturas;
                sf::Clock relogio;
                static float dt;

                static Gerenciador_Grafico* pGrafico; // static Singleton* Instance();

                // sf::Texture texturaFundo; 
                //sf::Sprite fundo;

                //sf::Font fonteMenu;

                // sf::Texture texturaAnakin;
                //sf::Sprite anakin;

                sf::Text textIniciar;
                sf::Text textRank;
                sf::Text textLoad;
                sf::Text textFase;
                sf::Text textPlayers;
                sf::Text textRules;

                vector<sf::Text> textOptions;
                static short int optionSelected;
                static void destruirGGrafico();

            protected:
                // Padrão de projeto Singleton 
                // (conhecido pelos vídeos do canal Gege++)
                Gerenciador_Grafico();  // Singleton();
            
            public:
                
                ~Gerenciador_Grafico();
                static Gerenciador_Grafico* getGerenciadorGrafico(); // static Singleton* _instance;
                void desenharEnte (Ente* pE);
                void desenharTextoMenu (sf::RenderWindow & janela); //out
                void desenharMenu (Menu* pM, sf::RenderWindow & janela); //out
                void desenharFase(Fase* pF, sf::RenderWindow & janela);
                void desenharOrigem(sf::RenderWindow& window, const sf::Sprite& sprite); //Apenas para debugar colisão
                void posicionarEnte(Ente* pE);

                void window(Menu* pM, Fase** pF);
                //void loadMenu(Menu* pM); //out
                //void menuTextPlacement(); //out
                
                static float getDeltaTempo();
                void atualizarTempoPercorrido();
                
                sf::Texture* carregarTextura (const char* path);
        };
    }
}
