#ifndef _PTHREAD_QUICKSORT_H_
#define _PTHREAD_QUICKSORT_H_
#include <sys/time.h>
#include <pthread.h>
#include "helpers.h"

/* QUICKSORT PARAMETER STRUCT */
struct quicksort_params{
  int *array;
  int low;
  int high;
} quicksort_params;

void parallel_quicksort(int *array, int low, int high);
int pivot_partition(int *array, int low, int high, int pivot);
void* quicksort_thread_utility(void * parameter_values);
void parallel_quicksort(int *array, int low, int high);
float get_pthread_benchmark(unsigned int* array, int SIZE);

#endif