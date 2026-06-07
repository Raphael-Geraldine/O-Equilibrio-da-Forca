#pragma once

#include"../include/Ente.h"
#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Entidades
    {
        class Entidade : public Ente
        {
            protected: //deve ser protected e ter get!!! está assim para testar
                float x;
                float y;
                //ostream buffer;
            
            protected:
                Entidade();
                void salvarDataBuffer();

            public:
                // Parâmetros remetem a vetores unitários.
                // Para evitar uso de "this" nesse caso.
                void setX(int i);
                float getX() const;
                void setY(int j);
                float getY() const;

                virtual ~Entidade();
                virtual void executar() = 0;
                virtual void salvar() = 0;
                virtual void mover() = 0; //lembrar que apenas personagens movem!
                virtual sf::Sprite getDrawData() = 0;
                virtual sf::FloatRect getBounds() const = 0;
        };
    }
}
