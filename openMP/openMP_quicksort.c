#include <sys/time.h>
#include <omp.h>
#include "../helpers.c"

#define DEBUG
#define SIZE 500000
#define SIZE_PRINT_LIMIT 100
#define THREAD_COUNT 8

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

/* QUICKSORT HELPER METHODS */

void swap_numbers(int* one, int* two){
    int temp = *one;
    *one = *two;
    *two = temp;
}

int partition(int* array, int low, int high){
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

void omp_quicksort(unsigned int* array, int low, int high){
    if(low < high){
        int partition_value = partition(array, low, high);
        #pragma omp task firstprivate(array, low, partition_value)
        {
            omp_quicksort(array, low, partition_value - 1);
        }
        {
            omp_quicksort(array, partition_value + 1, high);
        }
    }
}

void run_omp_quicksort(unsigned int* array){
    omp_set_num_threads(THREAD_COUNT);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp single nowait
        omp_quicksort(array, 0, SIZE - 1);
    }
    
}

float get_omp_benchmark(unsigned int* array){
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
    run_omp_quicksort(array);

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
    return time;
}


int main(){
    printf("Sorting array with %d elements using OpenMP...\n", SIZE);
    // Create array to be sorted
    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);
    float benchmark = get_omp_benchmark(array);
    free(array);
    return 0;
}