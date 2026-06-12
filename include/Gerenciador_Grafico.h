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
    class Principal;
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
                sf::Clock typingDelay;
                static float dt;

                static Gerenciador_Grafico* pGrafico; // static Singleton* Instance();

                // sf::Texture texturaFundo; 
                //sf::Sprite fundo;

                //sf::Font fonteMenu;
                sf::Font fonteName;
                sf::Text nameType;

                // sf::Texture texturaAnakin;
                //sf::Sprite anakin;

                //sf::Text textIniciar;
                //sf::Text textRank;
                //sf::Text textLoad;
                //sf::Text textFase;
                //sf::Text textPlayers;
                //sf::Text textRules;

                static void destruirGGrafico();

            protected:
                // Padrão de projeto Singleton 
                // (conhecido pelos vídeos do canal Gege++)
                Gerenciador_Grafico();  // Singleton();
            
            public:
                
                ~Gerenciador_Grafico();
                static Gerenciador_Grafico* getGerenciadorGrafico(); // static Singleton* _instance;
                sf::RenderWindow* getJanela();
                void desenharEnte (const Ente* pE);
                void desenharTextoMenu (vector<sf::Text>& text);
                void desenharMenu (Menu* pM, vector<sf::Text>& text);
                void desenharRank(sf::RenderWindow& janela, vector<Ranking*> jogsRank, sf::Sprite& fundo);
                void desenharFase(Fase* pF, sf::RenderWindow & janela);
                void desenharVida(sf::RenderWindow& janela, Jogador* pJ1, Jogador* pJ2);
                void desenharComoJogar(sf::RenderWindow& janela, sf::Sprite& fundo);
                void desenharOrigem(sf::RenderWindow& window, const sf::Sprite& sprite); //Apenas para debugar colisão
                void posicionarEnte(Ente* pE);

                void desenharSolicitar1Nome(sf::RenderWindow& janela, sf::Event& event, const sf::Sprite& fundo, string& nome);

                //void window(Menu* pM, Principal* pP);
                //void loadMenu(Menu* pM); //out
                //void menuTextPlacement(); //out
                
                static float getDeltaTempo();
                void atualizarTempoPercorrido();
                
                sf::Texture* carregarTextura (const char* path);
        };
    }
}
