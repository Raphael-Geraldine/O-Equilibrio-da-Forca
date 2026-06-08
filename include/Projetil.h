#pragma once

#include "../include/Entidade.h"
#include "../include/AT_ST.h"
#include "../include/Jogador.h"

#include <SFML/Graphics.hpp>

namespace TrabalhoJogo
{
    namespace Entidades
    {
        class Projetil : public Entidade
        {
            private:
                sf::Sprite projetilSkin;

            protected:
                bool ativo;
                short int dano;

            public:
                Projetil(short int d);
                ~Projetil();
                void executar();
                void salvar();
                void mover();
                void danificar(Personagens::Jogador* pJog);
                void perseguir(Personagens::Jogador* pJog, Personagens::AT_ST* pAT);
                void atualizarPosicaoSprite();
                sf::Sprite getDrawData();
                sf::FloatRect getBounds() const;
        };
    }
}