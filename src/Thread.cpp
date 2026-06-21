/*
Classe Thread:

O desenvolvimento desta classe foi 
baseado nos slides dados em aula da
disciplina de Técnicas de Programação, 
pelo prof. Dr. Jean Simão, em 2026/1.

*/

#include <iostream>
using namespace std;

#include "../include/Thread.h"
using namespace OEquilibrioDaForca;

pthread_mutex_t OEquilibrioDaForca::Thread::mutex;

Thread::Thread(): mutexIniciado(false)
{
    if (pthread_mutex_init(&mutex, NULL) == 0) 
        mutexIniciado = true;
}

Thread::~Thread()
{
}

void Thread::start()
{
    int status = pthread_create( &thread, NULL, &Thread::runThread, (void*)this);
    if ( status != 0)
        cerr<<"Falha ao iniciar a thread."<<endl;
}

void* Thread::runThread(void* p)
{
    Thread* sThread = static_cast<Thread*>(p);
    if ( NULL == sThread )
        cerr << "Thread falhou" <<endl;
    return sThread->run();
}

void Thread::join()
{  
    int status = pthread_join( thread, NULL );
    if ( status != 0)
        cerr<<"comando join falhou."<<endl;
}

void Thread::yield()
{
    sched_yield();
}

void Thread::lock()
{
    if (!mutexIniciado)
        pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
}

void Thread::unlock()
{
    if (mutexIniciado)
        pthread_mutex_unlock(&mutex);
}
