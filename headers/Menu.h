#pragma once
#include <vector>
#include <string>
using namespace std;

#include <SFML/graphics.hpp>

namespace TrabalhoJogo 
{ 
    namespace Gerenciadores 
    { 
        class Gerenciador_Grafico;
    }
}

namespace TrabalhoJogo
{
    class Menu /*: public Ente*/
    {
        private:
            //O_Equilibrio_da_Forca* pJogo;
            vector<string> fases;
            vector<string>::iterator faseEscolhida;
            int qntdJogadores;
            TrabalhoJogo::Gerenciadores::Gerenciador_Grafico* gGraf;

        public:
            Menu();
            ~Menu();
            void executar();
            bool CliqueDeRedirecionamento(sf::RenderWindow& janela, sf::Text& text);

    };
}