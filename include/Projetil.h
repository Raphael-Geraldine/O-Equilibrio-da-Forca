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

                float massa;
                float coefArrasto;
                float densidadeAr;
                float areaSecao;
                float moduloVelLancamento;

            private:
                float calcularModulo (const sf::Vector2f& vetor) const;
                sf::Vector2f normalizar (const sf::Vector2f& vetor) const;

                float calcularVelTerminal() const;
                sf::Vector2f calcularAcelArrasto() const;

                void aplicarFisica();
                void desativar();
                void atualizarRotacaoSprite();

            protected:
                bool ativo;
                short int dano;

            public:
                Projetil(short int d = 20);
                Projetil(float sx, float sy, float velx, float vely,short int d, bool a);
                ~Projetil();
                void executar();
                void salvar();
                void mover();
                void danificar(Personagens::Jogador* pJog);
                void perseguir(Personagens::Jogador* pJog, Personagens::AT_ST* pAT);
                void atualizarPosicaoSprite();
                sf::Sprite getDrawData() const;
                sf::FloatRect getBounds() const;
                bool getAtivo() const;
        };
    }
}