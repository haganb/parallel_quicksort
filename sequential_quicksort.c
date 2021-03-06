#include "sequential_quicksort.h"
//#define DEBUG
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

/* SEQUENTIAL QUICKSORT METHODS */

int sequential_partition(int* array, int low, int high){
    int pivot = array[high];
    int i = low - 1;
    for(int j = low; j <= high - 1; j++){
        if(array[j] <= pivot){
            i++;
            swap_numbers(&array[i], &array[j]);
        }
    }
    swap_numbers(&array[i+1], &array[high]);
    return i + 1;
}

void sequential_quicksort(int* array, int low, int high){
    if(low < high){
        int p = sequential_partition(array, low, high);
        sequential_quicksort(array, low, p - 1);
        sequential_quicksort(array, p +1, high);
    }
}

/* BENCHMARKING FUNCTION */
// get_cpu_benchmark: method to use radix sort on CPU and benchmark
float get_cpu_benchmark(unsigned int *array, int SIZE){
    // Set up benchmarking tools
    struct timespec begin;
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &begin);
    
    // Actual sorting
    sequential_quicksort(array, 0, SIZE - 1);

    // Finish benchmarking
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time = end.tv_sec - begin.tv_sec;
    time += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf("Elapsed time for sequential sorting: %lf second(s)\n", time);

    // Ensure that device is properly sorted
    if(check_if_sorted(array, SIZE)){
        printf("Array was sorted ");
        printf(ANSI_GREEN "successfully." ANSI_RESET "\n");
    }else{
        printf("ERROR: Array sorting ");
        printf(ANSI_RED "failed." ANSI_RESET "\n");
    }
    printf("\n");
    return time;
}