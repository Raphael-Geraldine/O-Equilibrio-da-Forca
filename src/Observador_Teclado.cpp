#include "../include/Observador_Teclado.h"
#include "../include/Gerenciador_Eventos.h"
#include "../include/Jogo.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

Observador_Teclado::Observador_Teclado():
    pJogo(NULL)
{
}

Observador_Teclado::~Observador_Teclado()
{
    pJogo = NULL;
}

void Observador_Teclado::setJogo(Jogo* pJ) 
{
    pJogo = pJ;
}

void Observador_Teclado::atualizar(Observado* pObservado) 
{
    if (pJogo == NULL)
    {
        cerr << "Ponteiro de jogo nulo. " << endl;
        return;
    }

    if (pObservado == NULL) 
    {
        cerr << "Ponteiro de observado nulo. " << endl;
        return;
    }

    Gerenciador_Eventos* pGerEventos = static_cast<Gerenciador_Eventos*>(pObservado);

    const sf::Event& evento = pGerEventos->getEvento();
    sf::RenderWindow* pJanela = pGerEventos->getJanela();

    if (pJanela == NULL)
    {
        cerr << "Ponteiro de janela nulo no Observador_Menu." << endl;
        return;
    }

    if (evento.type == sf::Event::Closed)
    {
        pJogo->fecharJogo(*pJanela);
        return;
    }

    else if (evento.type == sf::Event::KeyPressed) 
    {   
        /*
        if (((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) 
            || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            && (evento.key.code == sf::Keyboard::S))
        {
            pJogo->atalhoSalvarESair(*pJanela);
            return;
        }*/

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

    else
        return;
}