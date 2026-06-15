#pragma once

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
            virtual void* run() = 0;

        public:
            Thread();
            virtual ~Thread();
            void start(); // cria a thread;
            void join(); // espera a thread acabar;
            void yield(); // libera o processador;
            void lock();
            void unlock();

    };
}