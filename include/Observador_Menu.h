#pragma once

#include <vector>
using std::vector;

#include <SFML/Graphics.hpp>
#include "Observador_Eventos.h"

namespace OEquilibrioDaForca
{
    class Menu;
    enum class Estado;

    namespace Gerenciadores
    {
        class Observador_Menu: public Observador_Eventos
        {
            private:
                Menu* pMenu;
                Estado* pEstadoAtual;
                vector<sf::Text>* pVetTextosMenu;
                bool ativo;

            public:
                Observador_Menu();
                ~Observador_Menu();

                void setMenu(Menu* pM);
                void setEstadoAtual(Estado* pEstado);
                void setTextosMenu(vector<sf::Text>* pVTextos);
                void setAtivo (bool ativ);
                void atualizar (Observado* pObservado);
        };

    }
}