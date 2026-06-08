#pragma once

//#include "../include/Projetil.h"
#include "../include/Entidade.h"
#include "../include/Personagem.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Entidades
    {
        namespace Personagens
        {
            class AT_ST : public Inimigo
            {
                private:
                    float altura;
                    sf::Sprite atSkin;
                    bool directionMov;

                public:
                    AT_ST();
                    ~AT_ST();
                    void executar();
                    void danificar(Jogador* p);
                    sf::Sprite getDrawData();
                    sf::FloatRect getBounds() const;
                    void salvar();
                    void mover();
                    void operator++(); //aumentar o dano com pouca vida
                    void atualizarPosicaoSprite();
                    //void atirar(Jogador* pJog, Projetil* pP)
            };
        }
    }
}
