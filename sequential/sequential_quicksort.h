#ifndef _SEQUENTIAL_QUICKSORT_H_
#define _SEQUENTIAL_QUICKSORT_H_
#include <sys/time.h>
#include "../helpers.h"

void swap_numbers(int* one, int* two);

int partition(int* array, int low, int high);

void sequential_quicksort(int* array, int low, int high);

float get_cpu_benchmark(unsigned int *array);
#endif