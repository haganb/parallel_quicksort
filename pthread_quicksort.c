#include "pthread_quicksort.h"
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

// global variable to track number of threads
int THREAD_COUNT = 0;

// function needs to be declared for pthread
void parallel_quicksort(int *array, int low, int high);

/* QUICKSORT METHODS */

// Helper function to partition array and swap relevant values
int pivot_partition(int *array, int low, int high, int pivot){
	int pivot_value = array[pivot];
    swap_numbers(&array[pivot], &array[high]);
	int s = low;
	for (int i = low; i < high; i++){
		if (array[i] <= pivot_value){
			swap_numbers(&array[i], &array[s]);
            s++;
		}
	}
	swap_numbers(&array[s], &array[high]);
	return s;
}

//  pthread workload function: Pass in parameter values as void pointer, re-make struct, call actual quicksort method using parameters
void* quicksort_thread_utility(void * parameter_values){
  struct quicksort_params *parameters = parameter_values;
  parallel_quicksort(parameters->array, parameters->low, parameters->high);
  return NULL;
}

// Actual function to run parallelized quicksort
void parallel_quicksort(int *array, int low, int high){
    if (low < high){
        THREAD_COUNT++; // keep track of how many threads are spawned
        int pivot_position = low + (high - low) / 2;
        pivot_position = pivot_partition(array, low, high, pivot_position);
        pthread_t thread;
        struct quicksort_params thread_parameters = {array, low, pivot_position - 1};
        int thread_create = pthread_create(&thread, NULL, quicksort_thread_utility, &thread_parameters);
        parallel_quicksort(array, pivot_position + 1, high);
        pthread_join(thread, NULL);
    }
}

/* BENCHMARKING METHOD */
// Returns actual float in case method needs to be called from other file
float get_pthread_benchmark(unsigned int* array, int SIZE){
    // struct timeval begin;
    // struct timeval end;
    struct timespec begin;
    struct timespec end;

    // gettimeofday(&begin, NULL);
    clock_gettime(CLOCK_MONOTONIC, &begin);
    // Actual sorting
    parallel_quicksort(array, 0, SIZE - 1);

    // Finish benchmarking and process
    // gettimeofday(&end, NULL);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time = end.tv_sec - begin.tv_sec;
    time += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf("Elapsed time for PTHREAD concurrent sorting: %lf second(s)\n", time);

    if(check_if_sorted(array, SIZE)){
        printf("Array was sorted ");
        printf(ANSI_GREEN "successfully." ANSI_RESET "\n");
    }else{
        printf("ERROR: Array sorting ");
        printf(ANSI_RED "failed." ANSI_RESET "\n");
    }
    printf("Total number of threads spawned: %d\n", THREAD_COUNT);
    printf("\n");
    return time;
}