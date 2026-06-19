#include "../include/Observador_Teclado.h"
#include "../include/Jogo.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

Observador_Teclado::Observador_Teclado():
    pJogo(nullptr)
{
}

Observador_Teclado::~Observador_Teclado()
{
    pJogo = nullptr;
}

void Observador_Teclado::setJogo(Jogo* pJ) 
{
    pJogo = pJ;
}

void Observador_Teclado::atualizar(const sf::Event& evento, sf::RenderWindow& janela) 
{
    if (pJogo == nullptr)
        return;

    if (evento.type == sf::Event::Closed)
    {
        pJogo->fecharJogo(janela);
        return;
    }

    if (evento.type == sf::Event::KeyPressed) 
    {   
        if (((evento.key.code == sf::Keyboard::LControl) || (evento.key.code == sf::Keyboard::RControl))
            && (evento.key.code == sf::Keyboard::S))
        {
            pJogo->atalhoSalvarESair(janela);
            return;
        }

        if (evento.key.code == sf::Keyboard::Enter)
        {
            pJogo->confirmarEntrada();
            return;
        }

        if ((evento.key.code == sf::Keyboard::LShift) || (evento.key.code == sf::Keyboard::RShift))
        {
            pJogo->voltarParaMenu();
            return;
        }

        if (evento.key.code == sf::Keyboard::P)
        {
            pJogo->alternarPause();
            return;
        }

        if (evento.key.code == sf::Keyboard::Escape)  
        {
            pJogo->voltarMenuPeloPause();
            return;
        }     
    }
}