// Subject

#include "../include/Observado.h"
#include "../include/Observador_Eventos.h"
using namespace OEquilibrioDaForca;
using namespace Gerenciadores; 

Observado::Observado()
{
    observadores.clear();
}

Observado::~Observado()
{
    observadores.clear();
}

void Observado::anexar(Observador_Eventos* pObs)
{
    if (pObs == NULL) 
        return;

    observadores.push_back(pObs);
}

void Observado::desanexar(Observador_Eventos* pObs)
{
    if (pObs == NULL) 
        return;

    observadores.remove(pObs);
}

// Notifica os observadores, passando ele mesmo como o objeto observado.
void Observado::notificar() 
{
    list<Observador_Eventos*>::iterator it;

    for (it = observadores.begin(); it != observadores.end(); ++it)
    {
        if (*it != NULL) 
            (*it)->atualizar(this); 
    }
}