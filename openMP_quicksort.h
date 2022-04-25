#ifndef _OPENMP_QUICKSORT_H_
#define _OPENMP_QUICKSORT_H_
#include <sys/time.h>
#include <omp.h>
#include "helpers.h"

int omp_partition(int* array, int low, int high);
void omp_quicksort(unsigned int* array, int low, int high);
void run_omp_quicksort(unsigned int* array, int SIZE);
float get_omp_benchmark(unsigned int* array, int SIZE);
#endif