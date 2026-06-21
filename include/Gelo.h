#pragma once

#include <vector>
using namespace std;

#include "../include/Jogador.h"
#include "../include/Inimigo.h"
#include "../include/Obstaculo.h"

#include "SFML/Graphics.hpp"

namespace OEquilibrioDaForca
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Gelo : public Obstaculo
            {
                private:
                    short int danosidade;
                    static short int cont;
                    static vector<sf::Vector2i> geloPositions;
                    short int nGelo;

                    vector<sf::Clock> clockDano;
                    vector<int> ids;

                public:
                    Gelo();
                    ~Gelo();
                    void desacelerar(Jogador* pJog);
                    void executar();
                    void salvar();
                    void obstaculizar(Jogador* pJog);
                    void obstaculizarInim(Inimigo* pInim);
                    void mover();
                    void danificar(Jogador* pJog, int dano);
                    sf::Sprite getDrawData() const;
                    sf::FloatRect getBounds() const;
            };
        }
    }
}