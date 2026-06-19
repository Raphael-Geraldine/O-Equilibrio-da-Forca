// Subject
#pragma once

namespace OEquilibrioDaForca 
{
    namespace Gerenciadores 
    {
        class Observador_Eventos;

        class Observado 
        {
            protected:
                Observado();

            public:
                virtual ~Observado();
                virtual void anexar(Observador_Eventos* pObs) = 0;
                virtual void desanexar(Observador_Eventos* pObs) = 0;
                virtual void notificar() = 0;
        };
    }
}
