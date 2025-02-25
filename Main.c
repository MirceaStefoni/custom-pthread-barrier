#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_barrier.h"
#include "jones_print.h"

my_barrier_t barrier_breakfast;
my_barrier_t barrier_work;
my_barrier_t barrier_school;
my_barrier_t barrier_math;
my_barrier_t barrier_football;
my_barrier_t barrier_dinner;

char *day[] = {"Monday","Tuesday","Wednsday","Thursday","Friday"};

// Thread function
void *LifeOfJones(void *var)
{
    char *name = (char *)var;

    // Se repeta pentru fiecare zi
    for(int i=0; i < 5; i++)
    {
        print_breakfast(name, day[i]);
        print_work(name);
        print_school(name);
        print_math(name);
        print_football(name);
        print_dinner(name, day[i]);
    }

    return NULL;
}


int main(void)
{
    const int NUM_THREADS = 6;
    pthread_t threads[NUM_THREADS];

    char *name[] = {"Mama", "Papa", "Alice", "Bob", "Chris", "Dave"};

    my_barrier_init(&barrier_breakfast, 6);
    my_barrier_init(&barrier_work, 2);
    my_barrier_init(&barrier_school, 4);
    my_barrier_init(&barrier_math, 2);
    my_barrier_init(&barrier_football, 2);
    my_barrier_init(&barrier_dinner, 6);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, LifeOfJones, (void *)name[i]);
    }



    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    my_barrier_destroy(&barrier_breakfast);
    my_barrier_destroy(&barrier_work);
    my_barrier_destroy(&barrier_school);
    my_barrier_destroy(&barrier_math);
    my_barrier_destroy(&barrier_football);
    my_barrier_destroy(&barrier_dinner);


    return 0;
}