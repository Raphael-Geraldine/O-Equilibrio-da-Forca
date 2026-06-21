#pragma once

#include <iostream>
using namespace std;

#include"../include/Ente.h"
#include <SFML/Graphics.hpp>

namespace OEquilibrioDaForca
{
    namespace Entidades
    {
        class Entidade : public Ente
        {
            protected:
                float x;
                float y;
                bool emSuperficie;

                //lógica da Thread para AT_ST
                bool derivadoThread;
                bool semaforoAberto;

                float dt;
                sf::Vector2f velocidade;

                sf::Sprite skin;

                static const float velocidadeMaxQueda;
                static const float gravidade;
                static const float pixelsPorMetro;
                static const float gravidadeReal;
                ostream* buffer;
            
            protected:
                Entidade();
                void salvarDataBuffer();

                // Sobrecarga de métodos
                void limitarVelTerminal();
                void limitarVelTerminal(float limite);

            public:
                virtual ~Entidade();
                // Parâmetros remetem a vetores unitários.
                // Para evitar uso de "this" nesse caso.
                void setX(float i);
                float getX() const;
                void setY(float j); 
                float getY() const;

                void setDeltaTempo (const float tempo);
                
                void gravitar();

                void setVelocidade (const sf::Vector2f vel);
                void setVelocidadeX (const float vx);
                void setVelocidadeY (const float vy);
                sf::Vector2f getVelocidade() const;

                void setBuffer(ostream* arquivo);

                //Os chefões são derivados da classe Thhread, portanto esse bool indica isso
                const bool getDerivadoThread() const;
                bool getSemaforo();
                void setSemaforo(bool b);

                virtual void aplicarFisica();

                virtual void* run();

                virtual void executar() = 0;
                virtual void salvar() = 0;
                virtual void mover() = 0; //lembrar que apenas personagens movem!
                virtual sf::Sprite getDrawData() const = 0;
                virtual sf::FloatRect getBounds() const = 0;
        };
    }
}
