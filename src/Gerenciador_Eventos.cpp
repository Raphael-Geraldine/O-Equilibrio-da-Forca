// Observado concreto

#include "../include/Gerenciador_Eventos.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

Gerenciador_Eventos::Gerenciador_Eventos():
    Observado(),
    pJanela(NULL)
{}

Gerenciador_Eventos::~Gerenciador_Eventos()
{
    pJanela = NULL;
}

void Gerenciador_Eventos::setEvento(const sf::Event& evento, sf::RenderWindow* pJ)
{
    eventoAtual = evento;
    pJanela = pJ;
}

const sf::Event& Gerenciador_Eventos::getEvento() const
{
    return eventoAtual;
}

sf::RenderWindow* Gerenciador_Eventos::getJanela() const
{
    return pJanela;
}

