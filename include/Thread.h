#pragma once

/*
Classe Thread:

O desenvolvimento desta classe foi 
baseado nos slides dados em aula da
disciplina de Técnicas de Programação, 
pelo prof. Dr. Jean Simão, em 2026/1.

*/

#include <pthread.h>

namespace OEquilibrioDaForca
{
    class Thread
    {
        private:
            pthread_t thread;
            static pthread_mutex_t mutex;
            bool mutexIniciado;

        private:
            static void* runThread(void* pThread);
            virtual void* run() = 0; //vitual pura, método implementado na classe filha AT_ST (chefão)

        public:
            Thread();
            virtual ~Thread();
            void start(); //Cria a thread
            void join(); //Espera a thread acabar
            void yield(); //Libera o processador
            void lock();
            void unlock();
    };
}