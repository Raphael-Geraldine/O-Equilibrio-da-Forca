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
using namespace OEquilibrioDaForca;
using namespace Fases;
using namespace Entidades;
using namespace Obstaculos;
using namespace Gerenciadores;

#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    class Jogo;
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

namespace OEquilibrioDaForca
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

                sf::Font fonteName;
                sf::Text nameType;

                static void destruirGGrafico();

            protected:
                // Padrão de projeto Singleton 
                // (conhecido pelos vídeos do canal Gege++)
                Gerenciador_Grafico();  // Singleton();
            
            public:
                
                ~Gerenciador_Grafico();
                static Gerenciador_Grafico* getGerenciadorGrafico(); // static Singleton* _instance;
                sf::RenderWindow* getJanela();
                void desenharEnte (Ente* pE);
                void desenharTextoMenu (vector<sf::Text>& text);
                void desenharMenu (Menu* pM, vector<sf::Text>& text);
                void desenharRank(const vector<string>& linhasRank, sf::Sprite& fundo);
                void desenharFase(Fase* pF);
                void desenharVida(Jogador* pJ1, Jogador* pJ2);
                void desenharComoJogar(sf::Sprite& fundo);
                void desenharMenuPause(sf::Sprite& pause);
                void mostrar();
                void posicionarEnte(Ente* pE);

                void desenharSolicitar1Nome(sf::Event& event, const sf::Sprite& fundo, string& nome);
                
                static float getDeltaTempo();
                void atualizarTempoPercorrido();
                
                sf::Texture* carregarTextura (const char* path);
        };
    }
}
