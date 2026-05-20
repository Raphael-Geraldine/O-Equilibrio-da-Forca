#pragma once

#include"../include/Ente.h"
using namespace TrabalhoJogo;

#include <SFML/graphics.hpp>

namespace TrabalhoJogo
{
    namespace Entidades
    {
        class Entidade : public Ente
        {
            protected:
                int x;
                int y;
                //ostream buffer;
            
            protected:
                Entidade();
                virtual ~Entidade();
                void salvarDataBuffer();

            public:
                virtual void executar() = 0;
                virtual void salvar() = 0;
                virtual void mover() = 0; //lembrar que apenas personagens movem!
                virtual sf::Sprite getDrawData() = 0;
        };
    }
}
