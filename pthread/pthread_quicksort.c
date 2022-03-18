#include <sys/time.h>
#include <pthread.h>
#include "../helpers.c"

#define DEBUG

#define SIZE 10
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

/* QUICKSORT PARAMETER STRUCT */

typedef struct qsort_starter{
  int *array;
  int low;
  int high;
  int threadDepth;
} quicksort_params;

/* QUICKSORT METHODS */
void swap_numbers(int* one, int* two){
    int temp = *one;
    *one = *two;
    *two = temp;
}

int partition (int *array, int low, int high, int pivot)
{
	int pivotValue = array[pivot];
    swap_numbers(&array[pivot],&array[high]); // pivot
	int s = low; // Index of smaller element

	for (int i = low; i <high; i++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (array[i] <= pivotValue)
		{
			swap_numbers(&array[i], &array[s]);
      s++; // increment index of smaller element
		}
	}
	swap_numbers(&array[s], &array[high]);
	return s;
}

void quickSort(int *array, int low, int high)
{
	if (low < high)
	{
    int pivotPosition = low+ (high-low)/2;
    pivotPosition= partition(array, low, high, pivotPosition);
		quickSort(array, low, pivotPosition - 1);
		quickSort(array, pivotPosition + 1, high);
	}
}

void concurrent_quickSort(int *array, int low, int high, int threadDepth);

void* quicksort_thread_utility(void * parameter_values){
  quicksort_params *parameters = parameter_values;
  concurrent_quickSort(parameters->array, parameters->low, parameters->high,parameters->threadDepth);
  return NULL;
}

void concurrent_quickSort(int *array, int low, int high, int threadDepth){
    if (low < high){
        int pivot_position = low + (high - low) / 2;
        pivot_position = partition(array, low, high, pivot_position);
        pthread_t thread;
        if (threadDepth > 0){
            quicksort_params thread_parameters = {array, low, pivot_position - 1, threadDepth};
            int result;
            //Creating the thread  by calling the pthread_create for the left part recursively
            result = pthread_create(&thread, NULL, quicksort_thread_utility, &thread_parameters);
            //calling recursively for second time for the right part (for the same thread)
            concurrent_quickSort(array, pivot_position + 1, high, threadDepth);
            pthread_join(thread, NULL);
        } else{
            quickSort(array, low, pivot_position - 1);
            quickSort(array, pivot_position + 1, high);
         }

    }

}

void pthread_quicksort_wrapper(unsigned int* array){
    int threadDepth = SIZE/5;
    concurrent_quickSort(array, 0, SIZE - 1, threadDepth);
    if(check_if_sorted(array, SIZE)){
        printf(ANSI_GREEN "Success!\n" ANSI_RESET);
    }else{
        printf(ANSI_RED "Failed!\n" ANSI_RESET);
    }
    printf("Array after sorting:\n");
    print_matrix(array, SIZE);
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
    printf("Array prior to sorting:\n");
    print_matrix(array, SIZE);
    pthread_quicksort_wrapper(array);
    free(array);

    return 0;
}