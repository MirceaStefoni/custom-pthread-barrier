#include <stdio.h>
#include <stdlib.h>
#include "my_barrier.h"
#include <pthread.h>

void my_barrier_init(my_barrier_t *barrier, int num_threads)
{
    pthread_mutex_init(&barrier->mutex, NULL); // Initializeaza mutex-ul
    pthread_cond_init(&barrier->cond, NULL); // Initializeaza variabila de conditie
    barrier->count = 0; // Se pune Count-ul pe 0, starea sa initiala
    barrier->num_threads = num_threads; // num_threads reprezinta numarul de thread-uri care participa la bariera
    barrier->phase = 0;
}

void my_barrier_wait(my_barrier_t *barrier)
{
    pthread_mutex_lock(&barrier->mutex); // Se face lock la mutex pentru intreaga bariera

    barrier->count++; // Se incrementeaza counter-ul

    // Daca count a ajuns la numarul de thread-uri
    if (barrier->count == barrier->num_threads)
    {
        // Ultimul thread care ajunge aici semnaleaza tuturor
        barrier->count = 0; // Reseteaza pentru a reutiliza bariera
        barrier->phase ^= 1; // Facem toggle pe 0 sau pe 1
        pthread_cond_broadcast(&barrier->cond);

        // Se face unlock la mutex
        pthread_mutex_unlock(&barrier->mutex);
    } 
    else 
    {
        unsigned int curent_phase = barrier->phase;

        // Toate celelalte thread-uri asteapta
        while(curent_phase == barrier->phase)
        {
            pthread_cond_wait(&barrier->cond, &barrier->mutex);
        }
        
        // Se face unlock la mutex
        pthread_mutex_unlock(&barrier->mutex);
    }
}

void my_barrier_destroy(my_barrier_t *barrier)
{
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
}
