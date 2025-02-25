#ifndef JONES_PRINT_H
#define JONES_PRINT_H

extern my_barrier_t barrier_breakfast;
extern my_barrier_t barrier_work;
extern my_barrier_t barrier_school;
extern my_barrier_t barrier_math;
extern my_barrier_t barrier_football;
extern my_barrier_t barrier_dinner;

void print_breakfast(const char* name, const char* day);

void print_work(const char* name);

void print_school(const char* name);

void print_math(const char* name);

void print_football(const char* name);

void print_dinner(const char* name, const char* day);

#endif