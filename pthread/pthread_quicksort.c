#include <sys/time.h>
#include <pthread.h>
#include "../helpers.c"

#define DEBUG

#define SIZE 50
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

/* QUICKSORT PARAMETER STRUCT */
typedef struct quicksort_params{
    int* array;
    int high;
    int low;
    int threadDepth;
} quicksort_params;

/* QUICKSORT METHODS */
void swap_numbers(int* one, int* two){
    int temp = *one;
    *one = *two;
    *two = temp;
}

int partition(int* array, int low, int high, int pivot){
    int new_pivot = array[pivot];
    swap_numbers(&array[pivot], &array[high]);
    int s = low;

    for(int i = low; i < high; i++){
        if(array[i] <= new_pivot){
            swap_numbers(&array[i], &array[s]);
        }
    }
    swap_numbers(&array[s], &array[high]);
    return s;
}



void quickSort(int *arr, int low, int high)
{
	if (low < high)
	{
    int pivotPosition = low+ (high-low)/2;
    pivotPosition= partition(arr, low, high, pivotPosition);
		quickSort(arr, low, pivotPosition - 1);
		quickSort(arr, pivotPosition + 1, high);
	}
}

void pthread_quicksort(int* array, int low, int high, int threadDepth); // declare before define for pthread
void* thread_quicksort_utility(void* values){
    quicksort_params* params = values;
    pthread_quicksort(params->array, params->low, params->high, params->threadDepth);
    return NULL;
}

// Wrapper function for quicksort that handles pthreading
void pthread_quicksort(int* array, int low, int high, int threadDepth){
    if(low < high){
        int pivot = partition(array, low, high, low + (high-low) / 2);
        pthread_t thread;

        if(threadDepth > 0){
            quicksort_params params = {array, low, pivot - 1, threadDepth};
            int result;
            result = pthread_create(&thread, NULL, thread_quicksort_utility, &params);
            pthread_quicksort(array, pivot + 1, high, threadDepth);
            pthread_join(thread, NULL);
        }else{
            quickSort(array, low, pivot - 1);
            quickSort(array, pivot + 1, high);
        }
    }
}

void pthread_quicksort_wrapper(unsigned int* array){
    int threadDepth = 4;
    pthread_quicksort(array, 0, SIZE - 1, threadDepth);
    if(check_if_sorted(array, SIZE)){
        printf("Success!");
    }else{
        printf("Failed!");
    }
}

/* BENCHMARKING METHODS */
float get_pthread_benchmark(unsigned int* array){
    struct timeval begin;
    struct timeval end;

    gettimeofday(&begin, NULL);

    // Actual sorting


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
    printf("\n");
    return time;
}


/* MAIN METHOD */
int main(){
    printf("Sorting array with %d elements using PTHREADS...\n", SIZE);
    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);
    pthread_quicksort_wrapper(array);


    return 0;
}