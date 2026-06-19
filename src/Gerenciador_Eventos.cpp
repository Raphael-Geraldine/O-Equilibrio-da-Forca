#include "../include/Gerenciador_Eventos.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores;

Gerenciador_Eventos::Gerenciador_Eventos()
{
    observadores.clear(); // Verificar.
}

Gerenciador_Eventos::~Gerenciador_Eventos()
{
    limpar();
}

void Gerenciador_Eventos::anexar(Observador* pObs)
{
    if (pObs == nullptr) 
        return;

    observadores.push_back(pObs);
}

void Gerenciador_Eventos::desanexar(Observador* pObs)
{
    observadores.remove(pObs);
}

void Gerenciador_Eventos::notificar(const sf::Event& evento, sf::RenderWindow& janela) 
{
    list<Observador*>::iterator it;

    for (it = observadores.begin(); it != observadores.end(); ++it)
    {
        if (*it != nullptr) 
            (*it)->atualizar(evento, janela);
    }
}

void Gerenciador_Eventos::limpar()
{
    observadores.clear();
}