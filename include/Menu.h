#pragma once
#include <vector>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo 
{ 
    namespace Gerenciadores 
    { 
        class Gerenciador_Grafico;
    }

    class Principal;
}

#include"../include/Ente.h"
using namespace TrabalhoJogo;

namespace TrabalhoJogo
{
    class Menu : public Ente
    {
        private:
            Principal* pJogo;
            vector<string> fases;
            vector<string>::iterator faseEscolhida;
            int qntdJogadores;
            Gerenciadores::Gerenciador_Grafico* pGGraf;

        public:
            Menu();
            ~Menu();
            void executar();
            bool CliqueDeRedirecionamento(sf::RenderWindow& janela, sf::Text& text);
            sf::Sprite getDrawData();
    };
}
