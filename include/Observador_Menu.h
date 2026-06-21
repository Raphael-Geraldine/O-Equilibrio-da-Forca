#pragma once

#include <vector>
using std::vector;

#include <SFML/Graphics.hpp>
#include "../include/Observador_Eventos.h"

#include "../include/Estado.h"
using namespace OEquilibrioDaForca;

namespace OEquilibrioDaForca
{
    class Menu;

    namespace Gerenciadores
    {
        class Observador_Menu: public Observador_Eventos
        {
            private:
                Menu* pMenu;
                Estado::Tipo* pEstadoAtual;
                vector<sf::Text>* pVetTextosMenu;
                bool ativo;

            public:
                Observador_Menu();
                ~Observador_Menu();

                void setMenu(Menu* pM);
                void setEstadoAtual(Estado::Tipo* pEstado);
                void setTextosMenu(vector<sf::Text>* pVTextos);
                void setAtivo (bool ativ);
                void atualizar (Observado* pObservado);
        };

    }
}