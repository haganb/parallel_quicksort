#include <sys/time.h>
#include <pthread.h>
#include "../helpers.c"

#define DEBUG
#define SIZE 5000
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

// global variable to track number of threads
int THREAD_COUNT = 0;

// function needs to be declared for pthread
void parallel_quicksort(int *array, int low, int high);

/* QUICKSORT PARAMETER STRUCT */
struct quicksort_params{
  int *array;
  int low;
  int high;
} quicksort_params;

/* QUICKSORT METHODS */

// Helper function to swap values of two integer pointers in memory
void swap_numbers(int* one, int* two){
    int temp = *one;
    *one = *two;
    *two = temp;
}

// Helper function to partition array and swap relevant values
int partition (int *array, int low, int high, int pivot)
{
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
        pivot_position = partition(array, low, high, pivot_position);
        pthread_t thread;
        struct quicksort_params thread_parameters = {array, low, pivot_position - 1};
        int thread_create = pthread_create(&thread, NULL, quicksort_thread_utility, &thread_parameters);
        parallel_quicksort(array, pivot_position + 1, high);
        pthread_join(thread, NULL);
    }
}

/* BENCHMARKING METHOD */
// Returns actual float in case method needs to be called from other file
float get_pthread_benchmark(unsigned int* array){
    #ifdef DEBUG
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Array prior to sorting: ");
            print_matrix(array, SIZE);
        }
    #endif
    
    struct timeval begin;
    struct timeval end;

    gettimeofday(&begin, NULL);

    // Actual sorting
    parallel_quicksort(array, 0, SIZE - 1);

    // Finish benchmarking and process
    gettimeofday(&end, NULL);
    float time = (float)((end.tv_usec - begin.tv_usec)) / 1000;
    printf("Elapsed time for PTHREAD concurrent sorting (ms): %f\n", time);

    if(check_if_sorted(array, SIZE)){
        printf("Matrix was sorted ");
        printf(ANSI_GREEN "successfully." ANSI_RESET "\n");

        #ifdef DEBUG
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Good sort: ");
            print_matrix(array, SIZE);
        }
        #endif
    }else{
        printf("ERROR: Matrix sorting ");
        printf(ANSI_RED "failed." ANSI_RESET "\n");

        #ifdef DEBUG
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Bad sort: ");
            print_matrix(array, SIZE);
        }
        #endif
    }
    printf("Total number of threads spawned: %d\n", THREAD_COUNT);
    return time;
}

/* MAIN METHOD */
int main(){
    printf("Sorting array with %d elements using PTHREADS...\n", SIZE);

    // Create array to be sorted
    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);
    float benchmark = get_pthread_benchmark(array);

    // Free array and exit
    free(array);
    return 0;
}