#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "my_barrier.h"

pthread_barrier_t pthread_barrier;
my_barrier_t my_barrier;


void do_work(void) 
{
    float sum = 0.0f;
    int N = 20;
    
    for (int i = 0; i < N; i++)
    {   
        sum += (float)i;
    }
}


void *threadFn_pthread(void *val)
{
    int REPEATS = *(int*)val;

    for(int i=0; i < REPEATS; i++)
    {
        do_work();
        pthread_barrier_wait(&pthread_barrier);
    }

    return NULL;
}

void *threadFn_mybarrier(void *val)
{
    int REPEATS = *(int *)val;

    for(int i=0; i < REPEATS; i++)
    {
        do_work();
        my_barrier_wait(&my_barrier);
    }

    return NULL;
}

int main(int argc, char** argv)
{

    if (argc != 3)
    {
        printf("./p <THREAD_COUNT> <REPEATS>");
        exit(-1);
    }

    int THREAD_COUNT = atoi(argv[1]);
    int REPEATS = atoi(argv[2]);

    struct timespec start, finish;
    double elapsed_mybarrier, elapsed_pbarrier;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Measuring my_barrier                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


    clock_gettime(CLOCK_MONOTONIC, &start); // measure wall clock time!

    pthread_t threads_1[THREAD_COUNT];

    my_barrier_init(&my_barrier, THREAD_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&threads_1[i], NULL, threadFn_mybarrier, (void *)&REPEATS);
    }


    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads_1[i], NULL);
    }

    my_barrier_destroy(&my_barrier);
    

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed_mybarrier = (finish.tv_sec - start.tv_sec);
    elapsed_mybarrier += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("my_barrier_finished\n");


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Measuring my_barrier                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


    clock_gettime(CLOCK_MONOTONIC, &start); // measure wall clock time!

    pthread_t threads_2[THREAD_COUNT];

    pthread_barrier_init(&pthread_barrier, NULL, THREAD_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&threads_2[i], NULL, threadFn_pthread, (void *)&REPEATS);
    }


    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads_2[i], NULL);
    }

    pthread_barrier_destroy(&pthread_barrier);
    

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed_pbarrier = (finish.tv_sec - start.tv_sec);
    elapsed_pbarrier += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("pthread_barrier_finished\n");


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                Printing                                                 //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


    printf("\n\n");
    printf("--------------------------------------------------------------------\n");
    printf("THREAD_COUNT: %d\n",THREAD_COUNT);
    printf("REPEATS: %d\n",REPEATS);
    printf("PTHREAD_BARRIER_TIME: %g\n",elapsed_pbarrier);
    printf("MY_BARRIER_TIME: %g\n",elapsed_mybarrier);
    printf("--------------------------------------------------------------------\n\n");

/*

    FILE *file1, *file2;

    // Deschide output_pbarrier.txt
    file1 = fopen("output_pbarrier.txt", "a");
    if (file1 == NULL)
    {
        perror("Error opening output_pbarrier.txt");
        return 1;
    }

    // Deschide output_mybarrier.txt
    file2 = fopen("output_mybarrier.txt", "a");
    if (file2 == NULL) 
    {
        perror("Error opening file2.txt");
        fclose(file1); 
        return 1;
    }

    // Append elapsed_pbarrier in file1
    fprintf(file1, "%g\n", elapsed_pbarrier);

    // Append elapsed_mybarrier in file2
    fprintf(file2, "%g\n", elapsed_mybarrier);


    fclose(file1);
    fclose(file2);

    */
    

    return 0;
}


/*
 
for 2 threads and 20 repeats and 50 examples

pbarrier:  0.000565
mybarrier: 0.000604


for 2 threads and 20000 repeats and 50 examples

pbarrier:  0.3774579
mybarrier: 0.40286358


for 4 threads and 200 repeats and 50 examples

pbarrier:  0.0061852922
mybarrier: 0.0083711902


for 4 threads and 20000 repeats and 50 examples

pbarrier:  0.57273494
mybarrier: 0.61067088


for 8 threads and 200 repeats and 50 examples

pbarrier:  0.014592234
mybarrier: 0.025436754


for 8 threads and 20000 repeats and 50 examples

pbarrier:  0.94601468
mybarrier: 1.1676926






*/