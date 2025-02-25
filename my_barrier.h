#ifndef MY_BARRIER_H
#define MY_BARRIER_H


typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int num_threads;
    unsigned int phase;
} my_barrier_t;

void my_barrier_init(my_barrier_t *barrier, int num_threads);
void my_barrier_wait(my_barrier_t *barrier);
void my_barrier_destroy(my_barrier_t *barrier);

#endif