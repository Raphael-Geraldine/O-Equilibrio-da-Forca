// Observado concreto

#include "../include/Gerenciador_Eventos.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

Gerenciador_Eventos::Gerenciador_Eventos():
    Observado(),
    pJanela(nullptr)
{
    observadores.clear(); // Verificar.
}

Gerenciador_Eventos::~Gerenciador_Eventos()
{
    limpar();
    pJanela = nullptr;
}

void Gerenciador_Eventos::anexar(Observador_Eventos* pObs)
{
    if (pObs == nullptr) 
        return;

    observadores.push_back(pObs);
}

void Gerenciador_Eventos::desanexar(Observador_Eventos* pObs)
{
    observadores.remove(pObs);
}

// Notifica os observadores, passando ele mesmo como o objeto observado.
void Gerenciador_Eventos::notificar() 
{
    list<Observador_Eventos*>::iterator it;

    for (it = observadores.begin(); it != observadores.end(); ++it)
    {
        if (*it != nullptr) 
            (*it)->atualizar(this); 
    }
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

void Gerenciador_Eventos::limpar()
{
    observadores.clear();
}