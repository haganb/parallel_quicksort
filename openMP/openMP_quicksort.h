#ifndef _OPENMP_QUICKSORT_H_
#define _OPENMP_QUICKSORT_H_
#include <sys/time.h>
#include <omp.h>
#include "../helpers.h"

void swap_numbers(int* one, int* two);
int partition(int* array, int low, int high);
void omp_quicksort(unsigned int* array, int low, int high);
void run_omp_quicksort(unsigned int* array);
float get_omp_benchmark(unsigned int* array);
#endif