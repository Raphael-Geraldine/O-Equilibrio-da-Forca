#pragma once

//ATENÇÃO!!!
//Template, implementar nesse .h 

namespace TrabalhoJogo
{
    namespace Lista
    {
        template <typename TL>
        class Lista
        {
            private:
                Elemento<TL>* pPrimeiro;
                Elemento<TL>* pUltimo;

            private:
                template <typename TE>
                class Elemento
                {
                    private:
                        Elemento<TE>* pProx;
                        TE* pInfo;

                    public:
                        Elemento();
                        ~Elemento();
                        void incluir(TE* p);
                        void setProx(Elemento<TE>* pE);
                        Elemento<TE>* getProximo() const; 
                };

            public:
                Lista();
                ~Lista();
                void incluir(TL* p);
                void limpar();
        };
    }
}