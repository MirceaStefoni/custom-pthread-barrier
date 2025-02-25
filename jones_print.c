#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "my_barrier.h"
#include "jones_print.h"

void print_breakfast(const char* name, const char* day)
{
    // Toata lumea asteapta dupa barrier_breakfast
    printf("It is %s and %s waits for breakfast\n",day ,name);
    my_barrier_wait(&barrier_breakfast);
    sleep(2);
    printf("%s has finished eating breakfast\n",name);
}

void print_work(const char* name)
{
    // Doar Mama si Papa asteapta dupa barrier_work
    if(!strcmp(name,"Mama") || !strcmp(name,"Papa"))
    {
        printf("%s waits to go to work\n",name);
        my_barrier_wait(&barrier_work);
        sleep(5);
        printf("%s has finished working\n",name);
        sleep(1);
    }

}

void print_school(const char* name)
{
    // Toti copii asteapta dupa barrier_school
    if(!strcmp(name,"Alice") || !strcmp(name,"Bob") || !strcmp(name,"Chris") || !strcmp(name,"Dave"))
    {
        printf("%s waits to go to school\n",name);
        my_barrier_wait(&barrier_school);
        sleep(4);
        printf("%s has finished school\n",name);
        sleep(1);
    }

}

void print_math(const char* name)
{
    // Alice si Bob asteapta dupa barrier_math
    if(!strcmp(name,"Alice"))
    {
        printf("Alice waits to do math with Bob\n");
        my_barrier_wait(&barrier_math);
        sleep(3);
        printf("Alice has finished doing math with Bob\n");
    }
    if(!strcmp(name,"Bob"))
    {
        printf("Bob waits to do math with Alice\n");
        my_barrier_wait(&barrier_math);
        sleep(3);
        printf("Bob has finished doing math with Alice\n");
    }
}

void print_football(const char* name)
{
    // Chris si Dave asteapta dupa barrier_football
    if(!strcmp(name,"Chris"))
    {
        printf("Chris waits to play football with Dave\n");
        my_barrier_wait(&barrier_football);
        sleep(3);
        printf("Chris has finished playing football with Dave\n");
    }
    if(!strcmp(name,"Dave"))
    {
        printf("Dave waits to play football with Chris\n");
        my_barrier_wait(&barrier_football);
        sleep(3);
        printf("Dave has finished playing football with Chris\n");
    }

}

void print_dinner(const char* name, const char* day)
{
    // Toti asteapta dupa barrier_dinner
    printf("%s waits for dinner\n",name);
    my_barrier_wait(&barrier_dinner);
    sleep(2);
    printf("%s is over and %s has finished eating dinner\n",day,name);
    sleep(6);

}