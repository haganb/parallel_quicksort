#include "../helpers.c"
#include <sys/time.h>

#define DEBUG

#define SIZE 50
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

/* SEQUENTIAL QUICKSORT METHODS */

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

void sequential_quicksort(int* array, int low, int high){
    if(low < high){
        int p = partition(array, low, high);
        sequential_quicksort(array, low, p - 1);
        sequential_quicksort(array, p +1, high);
    }
}

/* BENCHMARKING FUNCTION */
// get_cpu_benchmark: method to use radix sort on CPU and benchmark
float get_cpu_benchmark(unsigned int *array){
    // Set up benchmarking tools
    struct timeval begin;
    struct timeval end;
    gettimeofday(&begin, NULL);

    // Actual sorting
    sequential_quicksort(array, 0, SIZE - 1);

    // Finish benchmarking
    gettimeofday(&end, NULL);
    float host_time = (float)((end.tv_usec - begin.tv_usec)) / 1000;
    printf("Elapsed time for CPU-bound sorting (ms): %f\n", host_time);

    // Ensure that device is properly sorted
    if(check_if_sorted(array, SIZE)){
        printf("Host matrix was sorted ");
        printf(ANSI_GREEN "successfully." ANSI_RESET "\n");
        
        #ifdef DEBUG
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Good sort: ");
            print_matrix(array, SIZE);
        }
        #endif
    }else{
        printf("ERROR: Host matrix sorting ");
        printf(ANSI_RED "failed." ANSI_RESET "\n");

        #ifdef DEBUG
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Bad sort: ");
            print_matrix(array, SIZE);
        }
        #endif
    }
    printf("\n");
    return host_time;
}

/* MAIN */

int main(){
    printf("Sorting array with %d elements\n", SIZE);

    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);

    float sequential_time = get_cpu_benchmark(array);
    return 0;
}