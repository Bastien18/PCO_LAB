#include "mythread.h"
#include <pcosynchro/pcologger.h>
#include <pcosynchro/pcothread.h>
#include <atomic>

// Juste passer le type de la variable counter en atomic permet de résoudre les problèmes lié au problème de la partie 6 du labo
static volatile std::atomic<long unsigned int> counter;

void runTask(unsigned long nbIterations)
{
    long unsigned int i = 0;

    logger() << "Adresse du thread actuel : " << PcoThread::thisThread() << std::endl;

    while (i < nbIterations)
    {
        counter++;
        i++;
    }
}

void initCounter()
{
    counter = 0;
}

long unsigned int getCounter()
{
    return counter;
}
