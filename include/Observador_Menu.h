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
                vector<sf::Text>* pTextosMenu;
                bool ativo;
        };

    }
}