#pragma once

#include <iostream> 
using namespace std;

// A lista permite uma vista de alto nível, inclusive com operador
// para lidar como vector. Cabe ao elemento, classe aninhada, tratar
// de conhecer o próximo para garantir que a lista opere como simplesmente
// encadeada.

namespace TrabalhoJogo
{
    namespace Listas
    {
        // Lista template simplesmente encadeada.

        template <class TL>
        class Lista
        {
            private:
                template <class TE>
                class Elemento
                {
                    private:
                        Elemento<TE>* pProx;
                        TE* pInfo;

                    public:
                        Elemento();
                        ~Elemento();
                        
                        void setElProx(Elemento<TE>* pE);
                        Elemento<TE>* getElProx() const;
                        
                        // Incluir implementado equivalente a um setInfo().
                        void incluir(TE* p);
                        TE* getInfo() const;   

                };
        
        private:
            Elemento<TL>* pPrimeiro;
            Elemento<TL>* pUltimo;
            size_t tamanhoLista;

        public:
            Lista();
            ~Lista();
            
            // Poderiam ser privados?
            Elemento<TE>* getPrimeiro() const;
            Elemento<TE>* getUltimo() const; 
            size_t getTamanho() const;
            
            // Inspiração na implementação do Burda, 
            // vide vídeo 8 da playlist Tutorial Jogo SFML.
            TL* operator[](int indice);

            void remover(int id);
            void remover(TL* pinfo);

            void incluir(TL* p);
            void limpar();  
        };

        // Implementação do template Elemento (TE) //

        template <class TL>
        template <class TE>

        Lista<TL>::Elemento<TE>::Elemento(): 
            pProx(NULL),
            pInfo(NULL) 
        {}

        template <class TL>
        template <class TE>

        Lista<TL>::Elemento<TE>::~Elemento() { 
            pProx = NULL;
            pInfo = NULL; 
        }

        template <class TL>
        template <class TE>
        void Lista<TL>::Elemento<TE>::setElProx(Elemento<TE>* pE) { 
            pProx = pE; 
        }

        template <class TL>
        template <class TE>

        // Para que o compilador interprete como declaração.
        typename Lista<TL>::template Elemento<TE>* 
        Lista<TL>::Elemento<TE>::getElProx() const 
        { 
            return pProx; 
        }

        template <class TL>
        template <class TE>

        void Lista<TL>::Elemento<TE>::incluir(TE* p)
        {
            if (p == NULL) 
                cerr << "Ponteiro TE nulo! Nao incluido!" << endl; 

            else 
                pInfo = p;
        }

        template <class TL>
        template <class TE>

        TE* Lista<TL>::Elemento<TE>::getInfo() const 
        { 
            return pInfo; 
        }

        // Implementação do template Lista (TL) //

        template <class TL>
        Lista<TL>::Lista():  
            pPrimeiro (NULL),
            pAnterior (NULL),
            tamanhoLista (0)
        {}

        template <class TL>
        Lista<TL>::~Lista() 
        {
            limpar();
            pPrimeiro = NULL;
            pAnterior = NULL;
            tamanho = -1;
        }

        template <class TL>
        void Lista<TL>::incluir(TL* p) 
        {
            if (p == NULL) 
            {
                cerr << "Ponteiro TL nulo! Nao incluido!" << endl; 
            }

            else 
            {   
                Elemento<TL>* pAux = NULL;
                pAux = new Elemento<TL>();

                pAux->incluir(p);
                
                if (pPrimeiro == NULL) 
                {
                    pPrimeiro = pAux;
                    pUltimo = pAux;
                }

                else 
                {
                    getUltimo()->setElProx(pAux);
                    pUltimo = pAux;
                }

                tamanhoLista++;
            }
        }

        template <class TL>
        void Lista<TL>::limpar() 
        {
            Elemento<TL>* pAux = NULL;

            while(pPrimeiro != NULL) 
            {
                pAux = pPrimeiro->getElProx();
                delete pPrimeiro;
                pPrimeiro = pAux;
            }

            pUltimo = NULL;
            tamanhoLista = 0;
        }

        template <class TL>
        TL* Lista<TL>::operator[] (int indice) {
            if (indice < 0 || indice >= tamanhoLista) 
            {
                cerr << "Indice fora dos limites da lista. " << endl;
                return NULL;
            }

            Elemento<TL>* pAux = pPrimeiro;
            int i = 0;
            while (i < indice) 
            {
                pAux = pAux->getElProx();
                i++;
            }

            return pAux->getInfo();
        }

        template <class TL>
        size_t Lista<TL>::getTamanho() const {
            return tamanhoLista;
        }

        // Sobrecarga pertinente de método remover.

        template <class TL>
        void Lista<TL>::remover(int indice) {
            if (indice < 0 || indice >= tamanhoLista)
            {
                cerr << "Indice fora dos limites da lista. " << endl;
                return NULL;
            }

            Elemento<TL>* pAnte = NULL;
            Elemento<TL>* pAtual = pPrimeiro;

            TL* info = pAtual->getInfo();

            int i = 0;
            while (i < indice)
            {
                pAnte = pAtual;
                pAtual = pAnte->getElProx();
                i++;
            }

            if (pAtual == pPrimeiro) 
            {
                pPrimeiro = pAtual->getElProx();
            }

            else if (pAtual == pUltimo) 
            {
                pAnte->setElProx(NULL);
                pUltimo = pAnte;
            }

            else 
            {
                pAnte->setElProx(pAtual->getProx());
            }

            tamanhoLista--;
            delete pAtual;

            cout << "Elemento " << info << "removido da lista." << endl;
        }

        template <class TL>
        void Lista<TL>::remover(TL* pinfo) {

            if(pPrimeiro == NULL) {
                return; // Lista vazia.
            }
            Elemento<TL>* pAnte = NULL;
            Elemento<TL>* pAtual = pPrimeiro;

            TL* info = pAtual->getInfo();

            while (pAtual != NULL && pAux->getInfo() != pinfo)
            {
                pAnte = pAtual;
                pAtual = pAnte->getElProx();
            }

            if (pAtual == NULL) 
            {
                cout << "Elemento nao existe na lista" << endl;
                return;
            }

            if (pAtual == pPrimeiro) 
            {
                pPrimeiro = pAtual->getElProx();
            }

            else if (pAtual == pUltimo) 
            {
                pAnte->setElProx(NULL);
                pUltimo = pAnte;
            }

            else 
            {
                pAnte->setElProx(pAtual->getProx());
            }

            tamanhoLista--;
            delete pAtual;

            cout << "Elemento " << info << "removido da lista." << endl;
        }
    } using namespace Listas;
} using namespace TrabalhoJogo;
