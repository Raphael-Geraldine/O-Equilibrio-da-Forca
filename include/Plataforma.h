#pragma once

#include <vector>
using namespace std;

#include "../include/Obstaculo.h"
#include "../include/Jogador.h"

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Plataforma : public Obstaculo
            {
                private:
                    // Para evitar que o jogador fique exatamente encostado ou
                    // sobreposto após correçao de colisão (fonte de bugs).
                    static const float epsilonColisao;

                    // Coeficientes de restituição (de 0.0f a 1.0f):
                    static const float coefRestCabeca;
                    static const float coefRestPiso;
                    static const float coefRestLateral;

                    // Plataforma escorrega sem apoio suficiente.
                    static const float apoioMinimo;
                    static const float deslocamentoEscorrega;
                    static const float velocidadeEscorrega;

                    static short int cont;
                    static vector<sf::Vector2i> platPositions;
                    short int platID;
                    float largura;
                    sf::Texture platTexture;
                    sf::Sprite platSkin;
                    sf::IntRect platSize;

                    void fazEscorregar(Jogador* pJog, const sf::FloatRect& jogBounds, const sf::FloatRect& obsBounds); 

                public:
                    Plataforma(float l=0.0f);
                    ~Plataforma();
                    void executar();
                    void salvar();
                    void mover();
                    void obstaculizar(Jogador* pJog);
                    sf::Sprite getDrawData();
                    sf::FloatRect getBounds() const;
            };
        }
    }
}
