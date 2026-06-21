#include "../include/Observador_Menu.h"
#include "../include/Gerenciador_Eventos.h"
#include "../include/Menu.h"

#include <iostream>
using std::cerr;
using std::endl;

using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

Observador_Menu::Observador_Menu():
    Observador_Eventos(),
    pMenu(nullptr),
    pEstadoAtual(nullptr),
    pVetTextosMenu(nullptr),
    ativo(false)
{}

Observador_Menu::~Observador_Menu() 
{
    pMenu = nullptr;
    pEstadoAtual = nullptr;
    pVetTextosMenu = nullptr;
}

void Observador_Menu::setMenu(Menu* pM)
{
    pMenu = pM;
}

void Observador_Menu::setEstadoAtual(Estado::Tipo* pEstado)
{
    pEstadoAtual = pEstado;
}

void Observador_Menu::setTextosMenu (vector<sf::Text>* pVTextos)
{
    pVetTextosMenu = pVTextos;
}

void Observador_Menu::setAtivo (bool ativ)
{
    ativo = ativ;
}

void Observador_Menu::atualizar(Observado* pObservado)
{
    if (!ativo)
        return;

    if (pMenu == nullptr)
    {
        cerr << "Erro: Ponteiro de Menu nulo no Observador_Menu." << endl;
        return;
    }

    if (pEstadoAtual == nullptr)
    {
        cerr << "Erro: Ponteiro de Estado nulo no Observador_Menu." << endl;
        return;
    }

    if (pVetTextosMenu == nullptr)
    {
        cerr << "Erro: Ponteiro de textos do Menu nulo no Observador_Menu." << endl;
        return;
    }
    
    if (pObservado == nullptr)
    {
        cerr << "Erro: Ponteiro de Observado nulo no Observador_Menu." << endl;
        return;
    }

    Gerenciador_Eventos* pGerEventos = static_cast<Gerenciador_Eventos*>(pObservado);

    const sf::Event& evento = pGerEventos->getEvento();
    sf::RenderWindow* pJanela = pGerEventos->getJanela();

    if (pJanela == nullptr)
    {
        cerr << "Ponteiro de janela nulo no Observador_Menu." << endl;
        return;
    }

    if (evento.type != sf::Event::MouseButtonPressed)
        return;

    if (evento.mouseButton.button != sf::Mouse::Left)
        return;

    vector<sf::Text>& text = *pVetTextosMenu;

    if (text.size() < 6)
        return;
        
    if (pMenu->cliqueEmOpcao(*pJanela,text[0]))
    {
        pMenu->prepararTelaNome();
        *pEstadoAtual = Estado::NomeJog1;
        return;
    }

    if (pMenu->cliqueEmOpcao(*pJanela, text[1]))
    {
        *pEstadoAtual = Estado::Ranking;
        return;
    }

    if (pMenu->cliqueEmOpcao(*pJanela, text[2]))
    {
        *pEstadoAtual = Estado::Carregar;
        return;
    }

    if (pMenu->cliqueEmOpcao(*pJanela, text[3]))
    {
        pMenu->alternarFase(text);
        *pEstadoAtual = Estado::Menu;
        return;
    }

    if (pMenu->cliqueEmOpcao(*pJanela, text[4]))
    {
        pMenu->alternarQuantidadeJogadores(text);
        *pEstadoAtual = Estado::Menu;
        return;
    }
    if (pMenu->cliqueEmOpcao(*pJanela, text[5]))
    {
        *pEstadoAtual = Estado::ComoJogar;
        return;
    }
}