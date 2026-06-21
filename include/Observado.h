// Subject
#pragma once

#include <list>
using namespace std;

namespace OEquilibrioDaForca 
{
    namespace Gerenciadores 
    {
        class Observador_Eventos;

        class Observado 
        {
            private:
                list<Observador_Eventos*> observadores;
           
            protected:
                Observado();

            public:
                virtual ~Observado();

                virtual void anexar(Observador_Eventos* pObs);
                virtual void desanexar(Observador_Eventos* pObs);
                virtual void notificar();
        };
    }
}
